package de.fhg.iais.roberta.javaServer.resources;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import org.codehaus.jettison.json.JSONObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.google.inject.Inject;

import de.fhg.iais.roberta.brick.BrickCommunicator;
import de.fhg.iais.roberta.brick.Templates;
import de.fhg.iais.roberta.javaServer.provider.OraData;
import de.fhg.iais.roberta.persistence.util.DbSession;
import de.fhg.iais.roberta.util.ClientLogger;
import de.fhg.iais.roberta.util.Util;

@Path("/blocks")
public class RestBlocks {
    private static final Logger LOG = LoggerFactory.getLogger(RestBlocks.class);

    private final Templates templates;
    private final BrickCommunicator brickCommunicator;

    @Inject
    public RestBlocks(Templates templates, BrickCommunicator brickCommunicator) {
        this.templates = templates;
        this.brickCommunicator = brickCommunicator;
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response command(@OraData HttpSessionState httpSessionState, @OraData DbSession dbSession, JSONObject fullRequest) throws Exception {
        new ClientLogger().log(LOG, fullRequest);
        JSONObject response = new JSONObject();
        try {
            JSONObject request = fullRequest.getJSONObject("data");
            String cmd = request.getString("cmd");
            LOG.info("command is: " + cmd);
            response.put("cmd", cmd);
            if ( cmd.equals("setToken") ) {
                String token = request.getString("token");
                if ( this.brickCommunicator.aTokenAgreementWasSent(token) ) {
                    httpSessionState.setToken(token);
                    response.put("rc", "ok").put("message", Util.TOKEN_SET_SUCCESS);
                    LOG.info("success: token " + token + " is registered in the session");
                } else {
                    response.put("rc", "error").put("message", Util.TOKEN_SET_ERROR_NO_ROBOT_WAITING);
                    LOG.info("error: token " + token + " is not awaited and thus not registered in the session");
                }
            } else if ( cmd.equals("loadT") ) {
                String name = request.getString("name");
                String template = this.templates.get(name);
                if ( template == null ) {
                    response.put("rc", "error").put("message", Util.TOOLBOX_LOAD_ERROR_NOT_FOUND);
                    LOG.info("error: toolbox: " + name + " not found");
                } else {
                    response.put("rc", "ok").put("message", Util.TOOLBOX_LOAD_SUCCESS).put("data", template);
                    ;
                    LOG.info("success: toolbox: " + name + " returned to client");
                }
            } else {
                LOG.error("Invalid command: " + cmd);
                response.put("rc", "error").put("message", Util.COMMAND_INVALID);
            }
            dbSession.commit();
        } catch ( Exception e ) {
            dbSession.rollback();
            String errorTicketId = Util.getErrorTicketId();
            LOG.error("Exception. Error ticket: " + errorTicketId, e);
            response.put("rc", "error").put("message", Util.SERVER_ERROR).append("parameters", errorTicketId);
        } finally {
            if ( dbSession != null ) {
                dbSession.close();
            }
        }
        Util.addFrontendInfo(response, httpSessionState, this.brickCommunicator);
        return Response.ok(response).build();
    }
}