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

import cubicchunks.converter.lib.Registry;
import cubicchunks.converter.lib.conf.ConverterConfig;
import cubicchunks.converter.lib.convert.WorldConverter;
import cubicchunks.converter.lib.util.Utils;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import java.awt.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Consumer;
import java.util.function.Function;

public class GuiFrame extends JFrame {

    private boolean isConverting = false;
    private boolean hasChangedDst;

    private JButton convertBtn;
    private JProgressBar progressBar;
    private JProgressBar convertFill, ioFill;

    private JTextField srcPathField;
    private JTextField dstPathField;

    private String inFormat = "Anvil";
    private String outFormat = "CubicChunks";
    private String converterName = "Default";

    private JComboBox<ConverterDesc> selectConverter;

    public void init() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e) {
            throw new Error("System Look and Feel shouldn't throw exception", e);
        }
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setMinimumSize(new Dimension(640, 0));

        JPanel root = new JPanel(new BorderLayout());

        JPanel mainPanel = new JPanel(new GridBagLayout());

        JPanel selection = new JPanel(new GridBagLayout());
        addSelectFilePanel(selection, false);
        addSelectFilePanel(selection, true);

        convertBtn = new JButton("Convert");
        progressBar = new JProgressBar();
        convertFill = new JProgressBar();
        ioFill = new JProgressBar();

        GridBagConstraints gbc = new GridBagConstraints();

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        mainPanel.add(selection, gbc);

        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.gridwidth = 1;
        gbc.weightx = 0;
        gbc.fill = GridBagConstraints.NONE;
        gbc.anchor = GridBagConstraints.EAST;
        mainPanel.add(convertBtn, gbc);

        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 1;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        mainPanel.add(progressBar, gbc);

        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.gridwidth = 1;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        mainPanel.add(convertFill, gbc);

        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 1;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        mainPanel.add(ioFill, gbc);

        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.gridwidth = 1;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        JLabel label = new JLabel("WARNING: USE ON MODDED WORLDS AT YOUR OWN RISK! THIS IS NOT DESIGNED TO HANDLE THEM!");
        label.setForeground(Color.RED);
        mainPanel.add(label, gbc);

        JPanel formatSelect = new JPanel(new FlowLayout());
        {
            formatSelect.add(new JLabel("Converter: "));
            selectConverter = new JComboBox<>();
            for (Registry.ClassTriple<?, ?, ?> converter : Registry.getConverters()) {
                ConverterDesc desc = new ConverterDesc(
                        Registry.getReader(converter.getIn()),
                        Registry.getWriter(converter.getOut()),
                        Registry.getConverter(converter.getConverter())
                );
                selectConverter.addItem(desc);
            }

            selectConverter.setSelectedIndex(0);
            formatSelect.add(selectConverter);
        }

        gbc.gridx = 0;
        gbc.gridy = 5;
        gbc.gridwidth = 1;
        gbc.weightx = 1;
        gbc.fill = GridBagConstraints.NONE;
        mainPanel.add(formatSelect, gbc);

        root.add(mainPanel, BorderLayout.CENTER);
        root.setBorder(new EmptyBorder(10, 10, 10, 10));

        updateConvertBtn();
        convertBtn.addActionListener(x -> convert());

        progressBar.setPreferredSize(new Dimension(100, (int) convertBtn.getPreferredSize().getHeight()));
        convertFill.setPreferredSize(new Dimension(100, (int) convertBtn.getPreferredSize().getHeight()));
        ioFill.setPreferredSize(new Dimension(100, (int) convertBtn.getPreferredSize().getHeight()));

        this.add(root);

        this.pack();
        this.setMinimumSize(new Dimension(200, this.getHeight()));
        this.setTitle("CubicChunks Save Converter");
        this.setVisible(true);

    }

    private void addSelectFilePanel(JPanel panel, boolean isSrc) {
        JLabel label = new JLabel(isSrc ? "Source: " : "Destination: ");

        Path srcPath = Utils.getApplicationDirectory().resolve("saves").resolve("New World");
        Path dstPath = getDstForSrc(srcPath, outFormat);
        JTextField path = new JTextField((isSrc ? srcPath : dstPath).toString());
        if (isSrc) {
            this.srcPathField = path;
        } else {
            this.dstPathField = path;
        }
        JButton selectBtn = new JButton("...");

        GridBagConstraints gbc = new GridBagConstraints();

        gbc.gridy = isSrc ? 0 : 1;

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 0;
        gbc.weightx = 0;
        panel.add(label, gbc);

        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.gridx = 1;
        gbc.weightx = 1;
        panel.add(path, gbc);

        gbc.fill = GridBagConstraints.NONE;
        gbc.gridx = 2;
        gbc.weightx = 0;
        panel.add(selectBtn, gbc);

        selectBtn.addActionListener(e -> {
            JFileChooser chooser = new JFileChooser();
            chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            chooser.setDialogType(JFileChooser.CUSTOM_DIALOG);
            chooser.setMultiSelectionEnabled(false);
            chooser.setFileHidingEnabled(false);
            chooser.setCurrentDirectory(getDefaultSaveLocation().toFile());
            int result = chooser.showDialog(this, "Select");
            if (result == JFileChooser.APPROVE_OPTION) {
                onSelectLocation(isSrc, chooser, outFormat);
            }
        });
        selectBtn.setPreferredSize(new Dimension(30, (int) path.getPreferredSize().getHeight()));
        selectBtn.setMinimumSize(new Dimension(30, (int) path.getPreferredSize().getHeight()));

        path.getDocument().addDocumentListener(new DocumentListener() {

            @Override public void insertUpdate(DocumentEvent e) {
                update();
            }

            @Override public void removeUpdate(DocumentEvent e) {
                update();
            }

            @Override public void changedUpdate(DocumentEvent e) {
                update();
            }

            private void update() {
                if (!isSrc) {
                    hasChangedDst = true;
                }
                updateConvertBtn();
            }
        });


        label.setHorizontalAlignment(SwingConstants.RIGHT);
    }

    private void updateConvertBtn() {
        convertBtn.setEnabled(!isConverting && Utils.isValidPath(dstPathField.getText()) && Utils.fileExists(srcPathField.getText()));
    }

    private void onSelectLocation(boolean isSrc, JFileChooser chooser, String format) {
        Path file = chooser.getSelectedFile().toPath();

        if (isSrc) {
            srcPathField.setText(file.toString());
            if (!hasChangedDst) {
                dstPathField.setText(getDstForSrc(file, format).toString());
            }
        } else {
            dstPathField.setText(file.toString());
            hasChangedDst = true;
        }
        updateConvertBtn();
    }

    private Path getDstForSrc(Path src, String outFormat) {
        return src.getParent().resolve(src.getFileName().toString() + " - " + outFormat);
    }

    private Path getDefaultSaveLocation() {
        return Utils.getApplicationDirectory().resolve("saves");
    }

    private void convert() {
        if (!Utils.fileExists(srcPathField.getText())) {
            updateConvertBtn();
            return;
        }
        Path srcPath = Paths.get(srcPathField.getText());
        Path dstPath;
        try {
            dstPath = Paths.get(dstPathField.getText());
        } catch (InvalidPathException e) {
            updateConvertBtn();
            return;
        }
        if (Files.exists(dstPath) && !Files.isDirectory(dstPath)) {
            JOptionPane.showMessageDialog(this, "The destination is not a directory!", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            if (!Utils.isEmpty(dstPath)) {
                String[] options = {"Cancel", "Continue"};
                int result = JOptionPane.showOptionDialog(this, "The selected destination directory is not empty.\nThis may result in overwriting "
                        + "or losing all data in this directory!\n\nDo you want cancel and select another directory?",
                    "Warning", JOptionPane.DEFAULT_OPTION, JOptionPane.WARNING_MESSAGE, null, options, "Cancel");
                if (result == JOptionPane.CLOSED_OPTION) {
                    return; // assume cancel
                }
                if (result == 0) {
                    return;
                }
            }
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Error while checking if destination directory is empty!", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        progressBar.setStringPainted(true);
        convertFill.setStringPainted(true);
        ioFill.setStringPainted(true);
        isConverting = true;
        updateConvertBtn();

        ConverterDesc desc = (ConverterDesc) selectConverter.getSelectedItem();
        this.inFormat = desc.getIn();
        this.outFormat = desc.getOut();
        this.converterName = desc.getConverterName();

        AtomicBoolean failed = new AtomicBoolean(false);

        Runnable updateProgress = () -> {
            isConverting = false;
            progressBar.setString(failed.get() ? "Error" : "Done!");
            progressBar.setValue(0);
            convertFill.setValue(0);
            ioFill.setValue(0);
            updateConvertBtn();
        };

        Function<Consumer<Throwable>, ConverterConfig> configLoader = Registry.getConfigLoader(inFormat, outFormat, converterName);
        ConverterConfig conf = new ConverterConfig(new HashMap<>());
        if (configLoader != null) {
            try {
                conf = configLoader.apply(error -> {
                    JOptionPane.showMessageDialog(this, error, "Error", JOptionPane.ERROR_MESSAGE);
                    failed.set(true);
                });
            } catch (Exception ex) {
                if (!failed.get()) {
                    throw ex;
                } else {
                    // TODO: logging
                    ex.printStackTrace();
                    updateProgress.run();
                    return;
                }
            }
            if (failed.get()) {
                updateProgress.run();
                return;
            }
        }
        WorldConverter<?, ?> converter = new WorldConverter<>(
            Registry.getLevelConverter(inFormat, outFormat, converterName).apply(srcPath, dstPath),
            Registry.getReader(inFormat).apply(srcPath, conf),
            Registry.getConverter(inFormat, outFormat, converterName).apply(conf),
            Registry.getWriter(outFormat).apply(dstPath)
        );

        ConverterWorker w = new ConverterWorker(converter, progressBar, convertFill, ioFill, updateProgress, () -> failed.set(true), this);
        w.execute();
    }

    private static class ConverterDesc {
        private final String in;
        private final String out;
        private final String converterName;

        public ConverterDesc(String in, String out, String converterName) {
            this.in = in;
            this.out = out;
            this.converterName = converterName;
        }

        public String getIn() {
            return in;
        }

        public String getOut() {
            return out;
        }

        public String getConverterName() {
            return converterName;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            ConverterDesc that = (ConverterDesc) o;
            return in.equals(that.in) &&
                    out.equals(that.out) &&
                    converterName.equals(that.converterName);
        }

        @Override
        public int hashCode() {
            return Objects.hash(in, out, converterName);
        }

        @Override
        public String toString() {
            return in + " -> " + out + " (" + converterName + ")";
        }
    }
}
