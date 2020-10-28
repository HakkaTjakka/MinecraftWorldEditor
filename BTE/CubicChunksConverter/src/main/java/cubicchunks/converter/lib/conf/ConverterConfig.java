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
package cubicchunks.converter.lib.conf;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class ConverterConfig {
    private Map<String, Object> defaults;
    private Map<String, Object> overrides;

    public ConverterConfig(Map<String, Object> defaults) {
        this.defaults = new ConcurrentHashMap<>(defaults);
        this.overrides = new ConcurrentHashMap<>();
    }

    public void set(String location, Object value) {
        overrides.put(location, value);
    }

    public void setDefault(String location, Object defaultValue) {
        defaults.put(location, defaultValue);
    }

    public double getDouble(String location) {
        return ((Number) getValue(location)).doubleValue();
    }

    public float getFloat(String location) {
        return ((Number) getValue(location)).floatValue();
    }

    public int getInt(String location) {
        return ((Number) getValue(location)).intValue();
    }

    public long getLong(String location) {
        return ((Number) getValue(location)).longValue();
    }

    public boolean getBool(String location) {
        Object value = getValue(location);
        if (value instanceof Number) {
            return ((Number) value).longValue() != 0L;
        }
        return ((Boolean) getValue(location));
    }

    public String getString(String location) {
        return getValue(location).toString();
    }

    public Object getValue(String location) {
        if (overrides.containsKey(location)) {
            return overrides.get(location);
        }
        return this.defaults.get(location);
    }

    public boolean hasValue(String location) {
        return this.overrides.containsKey(location) || this.defaults.containsKey(location);
    }

    public Map<String, Object> getDefaults() {
        return new HashMap<>(defaults);
    }

    public Map<String, Object> getOverrides() {
        return new HashMap<>(overrides);
    }
}
