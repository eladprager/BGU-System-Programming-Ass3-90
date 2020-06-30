package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.rci.ObjectEncoderDecoder;
import bgu.spl.net.impl.rci.RemoteCommandInvocationProtocol;
import bgu.spl.net.srv.*;


import java.awt.print.Book;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StompServer {

    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            throw new Exception("arguments are invalid");
        }
        if (args[1].equals("tpc")) {
            Server.threadPerClient(
                    Integer.parseInt(args[0]), //port
                    StompMessagingProtocolImpl::new, //protocol factory
                    StompEncoderDecoderImpl::new //message encoder decoder factory
            ).serve();
        } else if (args[1].equals("reactor")) {
            Server.reactor(
                    Runtime.getRuntime().availableProcessors(),
                    Integer.parseInt(args[0]), //port
                    StompMessagingProtocolImpl::new, //protocol factory
                    StompEncoderDecoderImpl::new //message encoder decoder factory
            ).serve();

        }
    }
}
