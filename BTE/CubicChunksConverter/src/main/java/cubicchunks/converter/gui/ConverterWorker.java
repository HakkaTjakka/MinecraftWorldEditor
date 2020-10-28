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
package cubicchunks.converter.gui;

import static java.awt.GridBagConstraints.HORIZONTAL;
import static java.awt.GridBagConstraints.NONE;
import static java.awt.GridBagConstraints.NORTH;
import static java.awt.GridBagConstraints.NORTHWEST;

import cubicchunks.converter.lib.IProgressListener;
import cubicchunks.converter.lib.convert.WorldConverter;

import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.io.UnsupportedEncodingException;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JProgressBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingWorker;

public class ConverterWorker extends SwingWorker<Throwable, Void> {

    private final WorldConverter converter;
    private final Runnable onFail;
    private final JFrame parent;
    private JProgressBar progressBar;
    private JProgressBar convertQueueFill;
    private JProgressBar ioQueueFill;
    private Runnable onDone;

    public ConverterWorker(WorldConverter converter, JProgressBar progressBar, JProgressBar convertQueueFill,
        JProgressBar ioQueueFill, Runnable onDone, Runnable onFail, JFrame parent) {
        this.converter = converter;
        this.progressBar = progressBar;
        this.convertQueueFill = convertQueueFill;
        this.ioQueueFill = ioQueueFill;
        this.onDone = onDone;
        this.onFail = onFail;
        this.parent = parent;
    }

    @Override protected Throwable doInBackground() {
        try {
            this.converter.convert(new IProgressListener() {
                @Override public void update() {
                    publish();
                }

                @Override public IProgressListener.ErrorHandleResult error(Throwable t) {
                    try {
                        onFail.run();
                        CompletableFuture<ErrorHandleResult> future = new CompletableFuture<>();
                        EventQueue.invokeAndWait(() -> future.complete(showErrorMessage(t)));
                        return future.get();
                    } catch (Exception e) {
                        e.printStackTrace();
                        return ErrorHandleResult.STOP_KEEP_DATA;
                    }
                }
            });
        } catch (Throwable t) {
            t.printStackTrace();
            onFail.run();
            return t;
        }
        return null;
    }

    private IProgressListener.ErrorHandleResult showErrorMessage(Throwable error) {
        String[] options = {"Ignore", "Ignore all", "Stop, delete results", "Stop, keep result"};
        JPanel infoPanel = new JPanel(new GridBagLayout());

        Insets insets = new Insets(3, 10, 3, 10);

        JTextArea errorInfo = new JTextArea("An error occurred while converting chunks. Do you want to continue?");
        errorInfo.setLineWrap(true);
        errorInfo.setEditable(false);
        errorInfo.setEnabled(false);
        infoPanel.add(errorInfo, new GridBagConstraints(0, 0, 1, 1, 1, 1, NORTH, HORIZONTAL, insets, 0, 0));


        JTextArea exceptionDetails = new JTextArea(exceptionString(error));
        exceptionDetails.setEditable(false);
        exceptionDetails.setLineWrap(false);

        JScrollPane scrollPane = new JScrollPane(exceptionDetails);
        scrollPane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPane.setMinimumSize(new Dimension(100, 250));
        scrollPane.setMaximumSize(new Dimension(500, 320));
        scrollPane.setPreferredSize(new Dimension(640, 400));

        JButton moreDetails = new JButton();
        moreDetails.setText("Show details...");
        moreDetails.addActionListener(e -> {
            JOptionPane.showConfirmDialog(infoPanel, scrollPane, "Error details", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE);
        });
        infoPanel.add(moreDetails, new GridBagConstraints(0, 1, 1, 1, 1, 1, NORTHWEST, NONE, insets, 0, 0));

        int code = JOptionPane.showOptionDialog(
            parent,
            infoPanel,
            "An error occurred while converting chunks", 0, JOptionPane.ERROR_MESSAGE,
            null, options, "Ignore");
        if (code == JOptionPane.CLOSED_OPTION) {
            return IProgressListener.ErrorHandleResult.IGNORE;
        }
        switch (code) {
            case 0:
                return IProgressListener.ErrorHandleResult.IGNORE;
            case 1:
                return IProgressListener.ErrorHandleResult.IGNORE_ALL;
            case 2:
                return IProgressListener.ErrorHandleResult.STOP_DISCARD;
            case 3:
                return IProgressListener.ErrorHandleResult.STOP_KEEP_DATA;
            default:
                assert false;
                return IProgressListener.ErrorHandleResult.IGNORE;
        }
    }

    @Override protected void process(List<Void> l) {
        int submitted = converter.getSubmittedChunks();
        int total = converter.getTotalChunks();
        double progress = 100 * submitted / (float) total;
        String message = String.format("Submitted chunk tasks: %d/%d %.2f%%", submitted, total, progress);
        this.progressBar.setMinimum(0);
        this.progressBar.setMaximum(total);
        this.progressBar.setValue(submitted);
        this.progressBar.setString(message);

        int maxSize = this.converter.getConvertBufferMaxSize();
        int size = this.converter.getConvertBufferFill();
        this.convertQueueFill.setMinimum(0);
        this.convertQueueFill.setMaximum(maxSize);
        this.convertQueueFill.setValue(size);
        this.convertQueueFill.setString(String.format("Convert queue fill: %d/%d", size, maxSize));

        maxSize = this.converter.getIOBufferMaxSize();
        size = this.converter.getIOBufferFill();
        this.ioQueueFill.setMinimum(0);
        this.ioQueueFill.setMaximum(maxSize);
        this.ioQueueFill.setValue(size);
        this.ioQueueFill.setString(String.format("IO queue fill: %d/%d", size, maxSize));
    }

    @Override
    protected void done() {
        onDone.run();
        Throwable t;
        try {
            t = get();
        } catch (InterruptedException | ExecutionException e) {
            t = e;
        }
        if (t == null) {
            return;
        }
        JOptionPane.showMessageDialog(null, exceptionString(t));
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
