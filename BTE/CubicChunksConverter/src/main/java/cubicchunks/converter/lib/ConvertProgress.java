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
package cubicchunks.converter.lib;

public class ConvertProgress {

    private int step;
    private final int maxSteps;
    private double stepProgress;
    private final double maxStepProgress;
    private String stepName;

    public ConvertProgress(String stepName, int step, int maxSteps, double stepProgress, double maxStepProgress) {
        this.stepName = stepName;
        this.step = step;
        this.maxSteps = maxSteps;
        this.stepProgress = stepProgress;
        this.maxStepProgress = maxStepProgress;
    }

    public int getStep() {
        return step;
    }

    public int getMaxSteps() {
        return maxSteps;
    }

    public double getStepProgress() {
        return stepProgress;
    }

    public double getMaxStepProgress() {
        return maxStepProgress;
    }

    public String getStepName() {
        return stepName;
    }
}
