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
package cubicchunks.converter.headless;

import cubicchunks.converter.headless.command.HeadlessCommandContext;
import cubicchunks.converter.headless.command.HeadlessCommands;
import cubicchunks.converter.lib.Registry;
import cubicchunks.converter.lib.conf.ConverterConfig;
import cubicchunks.converter.lib.convert.WorldConverter;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Consumer;
import java.util.function.Function;

public class HeadlessConverter {

    public static void convert() {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        HeadlessCommandContext context = new HeadlessCommandContext();
        while(true) {
            if(context.getSrcWorld() == null || context.getDstWorld() == null || context.getInFormat() == null || context.getOutFormat() == null || context.getConverterName() == null) {
                try {
                    String line = br.readLine();
                    HeadlessCommands.handleCommand(context, line);
                } catch (IOException e) {
                    throw new Error(e);
                }
            } else
                break;
        }
        convert(context);
    }

    public static void convert(List<String> commands) {
        HeadlessCommandContext context = new HeadlessCommandContext();
        for (String command : commands) {
            String line = command;
            HeadlessCommands.handleCommand(context, line);
        }
        if(context.getSrcWorld() == null || context.getDstWorld() == null || context.getInFormat() == null || context.getOutFormat() == null || context.getConverterName() == null)
            throw new IllegalStateException("Incomplete arguments!\n" + context);
        convert(context);
    }

    private static void convert(HeadlessCommandContext context) {
        AtomicBoolean failed = new AtomicBoolean(false);
        Function<Consumer<Throwable>, ConverterConfig> configLoader = Registry.getConfigLoader(context.getInFormat(), context.getOutFormat(), context.getConverterName());
        ConverterConfig conf = new ConverterConfig(new HashMap<>());
        if (configLoader != null) {
            try {
                conf = configLoader.apply(error -> {
                    System.out.println(error.getMessage());
                    failed.set(true);
                });
            } catch (Exception ex) {
                if (!failed.get()) {
                    throw ex;
                } else {
                    // TODO: logging
                    ex.printStackTrace();
                    //updateProgress.run();
                    return;
                }
            }
            if (failed.get()) {
                //updateProgress.run();
                return;
            }
        }

        WorldConverter<?, ?> converter = new WorldConverter<>(
            Registry.getLevelConverter(context.getInFormat(), context.getOutFormat(), context.getConverterName()).apply(context.getSrcWorld(), context.getDstWorld()),
            Registry.getReader(context.getInFormat()).apply(context.getSrcWorld(), conf),
            Registry.getConverter(context.getInFormat(), context.getOutFormat(), context.getConverterName()).apply(conf),
            Registry.getWriter(context.getOutFormat()).apply(context.getDstWorld())
        );

        HeadlessWorker w = new HeadlessWorker(converter, HeadlessConverter::done, () -> failed.set(true));
        try {
            w.convert();
        } catch (IOException e) {
            failed.set(true);
            e.printStackTrace();
        }
    }

    private static void done() {

    }
}
