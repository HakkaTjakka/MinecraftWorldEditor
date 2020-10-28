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

import java.nio.file.Path;

public class HeadlessCommandContext {
    private Path srcWorld;
    private Path dstWorld;

    private String inFormat;
    private String outFormat;
    private String converterName = "Default";

    public Path getSrcWorld() {
        return srcWorld;
    }

    public void setSrcWorld(Path srcWorld) {
        this.srcWorld = srcWorld;
    }

    public Path getDstWorld() {
        return dstWorld;
    }

    public void setDstWorld(Path dstWorld) {
        this.dstWorld = dstWorld;
    }

    public String getInFormat() {
        return inFormat;
    }

    public void setInFormat(String inFormat) {
        this.inFormat = inFormat;
    }

    public String getOutFormat() {
        return outFormat;
    }

    public void setOutFormat(String outFormat) {
        this.outFormat = outFormat;
    }

    public String getConverterName() {
        return converterName;
    }

    public void setConverterName(String converterName) {
        this.converterName = converterName;
    }

    @Override
    public String toString() {
        return "HeadlessCommandContext{" +
            "srcWorld=" + srcWorld +
            ", dstWorld=" + dstWorld +
            ", inFormat='" + inFormat + '\'' +
            ", outFormat='" + outFormat + '\'' +
            ", converterName='" + converterName + '\'' +
            '}';
    }
}
