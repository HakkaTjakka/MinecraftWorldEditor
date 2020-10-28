/*
 *  This file is part of CubicChunksConverter, licensed under the MIT License (MIT).
 *
 *  Copyright (c) 2017 contributors
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
package cubicchunks.converter.headless.command;

import com.mojang.brigadier.CommandDispatcher;
import com.mojang.brigadier.StringReader;
import com.mojang.brigadier.exceptions.CommandSyntaxException;
import cubicchunks.converter.headless.command.commands.*;

import java.util.logging.Level;
import java.util.logging.Logger;

public class HeadlessCommands {
    private static final Logger LOGGER = Logger.getLogger(HeadlessCommands.class.getSimpleName());

    private static final CommandDispatcher<HeadlessCommandContext> dispatcher = new CommandDispatcher<>();

    static {
        SourceWorldCommand.register(dispatcher);
        DestinationWorldCommand.register(dispatcher);
        InFormatCommand.register(dispatcher);
        OutFormatCommand.register(dispatcher);
        ConverterNameCommand.register(dispatcher);
    }

    public static int handleCommand(HeadlessCommandContext context, String command) {
        StringReader stringreader = new StringReader(command);
        try {
            int execute = dispatcher.execute(stringreader, context);
            LOGGER.info("Parsed correctly: + " + command);
            return execute;
        } catch (CommandSyntaxException commandsyntaxexception) {
            LOGGER.log(Level.SEVERE, commandsyntaxexception.getMessage(), commandsyntaxexception);

            if (commandsyntaxexception.getInput() != null && commandsyntaxexception.getCursor() >= 0) {
                int j = Math.min(commandsyntaxexception.getInput().length(), commandsyntaxexception.getCursor());
                String errorMsg = "";

                if (j > 10)
                    errorMsg += "...";

                errorMsg += commandsyntaxexception.getInput().substring(Math.max(0, j - 10), j);
                if (j < commandsyntaxexception.getInput().length()) {
                    String subErr = commandsyntaxexception.getInput().substring(j);
                    errorMsg += subErr;
                }

                errorMsg += "<--[HERE]";
                LOGGER.severe(errorMsg);
            }
        } catch (Exception e) {
            LOGGER.severe(e.getMessage());
        }
        return 0;
    }
}
