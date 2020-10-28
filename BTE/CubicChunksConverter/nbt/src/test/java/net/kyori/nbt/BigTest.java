/*
 * This file is part of nbt, licensed under the MIT License.
 *
 * Copyright (c) 2017 KyoriPowered
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
package net.kyori.nbt;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Ensure that we can read the bigtest.nbt file.
 */
class BigTest {
  private static final double DOUBLE_DELTA = 1e-15;
  private static final byte[] BYTE_ARRAY_TEST = new byte[1000];
  private static final ListTag LONG_LIST = new ListTag();
  private static final ListTag COMPOUND_LIST = new ListTag();
  private static final CompoundTag NESTED_COMPOUND = new CompoundTag();
  private static CompoundTag compound;

  static {
    for(int i = 0; i < 1000; i++) {
      BYTE_ARRAY_TEST[i] = (byte) ((i * i * 255 + i * 7) % 100);
    }

    LONG_LIST.add(new LongTag(11));
    LONG_LIST.add(new LongTag(12));
    LONG_LIST.add(new LongTag(13));
    LONG_LIST.add(new LongTag(14));
    LONG_LIST.add(new LongTag(15));

    final CompoundTag listTestCompoundTag0 = new CompoundTag();
    listTestCompoundTag0.putLong("created-on", 1264099775885L);
    listTestCompoundTag0.putString("name", "Compound tag #0");
    final CompoundTag listTestCompoundTag1 = new CompoundTag();
    listTestCompoundTag1.putLong("created-on", 1264099775885L);
    listTestCompoundTag1.putString("name", "Compound tag #1");

    COMPOUND_LIST.add(listTestCompoundTag0);
    COMPOUND_LIST.add(listTestCompoundTag1);

    final CompoundTag egg = new CompoundTag();
    egg.putString("name", "Eggbert");
    egg.putFloat("value", 0.5f);
    final CompoundTag ham = new CompoundTag();
    ham.putString("name", "Hampus");
    ham.putFloat("value", 0.75f);

    NESTED_COMPOUND.put("egg", egg);
    NESTED_COMPOUND.put("ham", ham);
  }

  @BeforeAll
  static void before() throws IOException, URISyntaxException {
    final URL url = BigTest.class.getResource("/bigtest.nbt");
    compound = TagIO.readCompressedPath(TagTypeMaps.MINECRAFT, Paths.get(url.toURI()));
  }

  @Test
  void testCorrectValues() {
    assertEquals(Short.MAX_VALUE, compound.getShort("shortTest"));
    assertEquals(Long.MAX_VALUE, compound.getLong("longTest"));
    assertEquals(Byte.MAX_VALUE, compound.getByte("byteTest"));
    assertArrayEquals(BYTE_ARRAY_TEST, compound.getByteArray("byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"));
    assertEquals(LONG_LIST, compound.getList("listTest (long)"));
    assertEquals(0.49823147f, compound.getFloat("floatTest"), DOUBLE_DELTA);
    assertEquals(0.4931287132182315d, compound.getDouble("doubleTest"), DOUBLE_DELTA);
    assertEquals(Integer.MAX_VALUE, compound.getInt("intTest"));
    assertEquals(COMPOUND_LIST, compound.getList("listTest (compound)"));
    assertEquals(NESTED_COMPOUND, compound.getCompound("nested compound test"));
    assertEquals("HELLO WORLD THIS IS A TEST STRING ÅÄÖ!", compound.getString("stringTest"));
  }
}
