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

import cubicchunks.converter.lib.IProgressListener;
import cubicchunks.converter.lib.conf.command.EditTaskCommands;
import cubicchunks.converter.lib.convert.WorldConverter;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.logging.Logger;

public class HeadlessWorker {
    private final WorldConverter converter;
    private final Runnable onFail;
    private Runnable onDone;

    private long lastProcessTime = System.currentTimeMillis();

    private static final Logger LOGGER = Logger.getLogger(EditTaskCommands.class.getSimpleName());

    public HeadlessWorker(WorldConverter converter, Runnable onDone, Runnable onFail) {
        this.converter = converter;
        this.onDone = onDone;
        this.onFail = onFail;
    }

    protected void convert() throws IOException {
        this.converter.convert(new IProgressListener() {
            @Override public void update() {
                if(System.currentTimeMillis() - lastProcessTime > 300) {
                    process();
                    lastProcessTime = System.currentTimeMillis();
                }
            }

            @Override public IProgressListener.ErrorHandleResult error(Throwable t) {
                try {
                    onFail.run();
                    return showErrorMessage(t);
                } catch (Exception e) {
                    e.printStackTrace();
                    return ErrorHandleResult.STOP_KEEP_DATA;
                }
            }
        });
        onDone.run();
    }

    private IProgressListener.ErrorHandleResult showErrorMessage(Throwable error) {
        LOGGER.info(exceptionString(error));
        System.err.println("An error occurred while converting chunks. Do you want to continue?\n(I)gnore/ignore (A)ll/cancel and (K)eep results/cancel and (D)elete results");

        IProgressListener.ErrorHandleResult code = IProgressListener.ErrorHandleResult.IGNORE;

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        while(true) {
            try {
                String line = reader.readLine();
                if(!line.equals("")) {
                    char c = line.toUpperCase().charAt(0);
                        switch (c) {
                            case 'I':
                                return IProgressListener.ErrorHandleResult.IGNORE;
                            case 'A':
                                return IProgressListener.ErrorHandleResult.IGNORE_ALL;
                            case 'K':
                                return IProgressListener.ErrorHandleResult.STOP_KEEP_DATA;
                            case 'D':
                                return IProgressListener.ErrorHandleResult.STOP_DISCARD;
                        }
                }
            } catch (IOException e) {
                throw new Error(e);
            }
        }
    }

    protected void process() {
        int submitted = converter.getSubmittedChunks();
        int total = converter.getTotalChunks();
        double progress = 100 * submitted / (float) total;
        String messageRead = String.format("Submitted chunk tasks: %d/%d %.2f%%", submitted, total, progress);

        int maxSize = this.converter.getConvertBufferMaxSize();
        int size = this.converter.getConvertBufferFill();
        String messageConvert = String.format("Convert queue fill: %d/%d", size, maxSize);

        maxSize = this.converter.getIOBufferMaxSize();
        size = this.converter.getIOBufferFill();
        String messageWrite = String.format("IO queue fill: %d/%d", size, maxSize);

        System.out.println(messageRead + "\n" + messageConvert + "\n" + messageWrite);
    }

    private static String exceptionString(Throwable t) {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        PrintStream ps;
        try {
            ps = new PrintStream(out, true, "UTF-8");
        } catch (UnsupportedEncodingException e1) {
            throw new Error(e1);
        }
        t.printStackTrace(ps);
        ps.close();
        return new String(out.toByteArray(), StandardCharsets.UTF_8);
    }
}
