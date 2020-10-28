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

import com.google.common.io.ByteArrayDataInput;
import com.google.common.io.ByteArrayDataOutput;
import com.google.common.io.ByteStreams;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;

class ReadWriteTest {
  @Test
  void testByteArray() throws IOException {
    this.testWriteRead(new ByteArrayTag(new byte[]{Byte.MIN_VALUE, -100, 0, 100, Byte.MAX_VALUE}), new ByteArrayTag());
  }

  @Test
  void testByte() throws IOException {
    this.testWriteRead(new ByteTag((byte) 2), new ByteTag());
  }

  @Test
  void testCompound() throws IOException {
    final CompoundTag a = new CompoundTag();
    {
      a.putByte("AByte", (byte) 0);
      a.putInt("AnInt", 1);
      a.putIntArray("AnIntArray", new int[]{0, 1, 4, 5, 8, 9});
    }
    final CompoundTag b = new CompoundTag();
    this.testWriteRead(a, b);
    assertEquals(a.type(), b.type());
    assertEquals(a, b);
  }

  @Test
  void testDouble() throws IOException {
    this.testWriteRead(new DoubleTag(4d), new DoubleTag());
  }

  @Test
  void testEnd() throws IOException {
    this.testWriteRead(new EndTag(), new EndTag());
  }

  @Test
  void testFloat() throws IOException {
    this.testWriteRead(new FloatTag(6f), new FloatTag());
  }

  @Test
  void testIntArray() throws IOException {
    this.testWriteRead(new IntArrayTag(new int[]{Integer.MIN_VALUE, -100, 0, 100, Integer.MAX_VALUE}), new IntArrayTag());
  }

  @Test
  void testInt() throws IOException {
    this.testWriteRead(new IntTag(8), new IntTag());
  }

  @Test
  void testList() throws IOException {
    final ListTag a = new ListTag(TagType.DOUBLE);
    {
      a.add(new DoubleTag(32d));
      a.add(new DoubleTag(64d));
    }
    final ListTag b = new ListTag();
    this.testWriteRead(a, b);
    assertEquals(a.type(), b.type());
    assertEquals(a, b);
  }

  @Test
  void testLongArray() throws IOException {
    this.testWriteRead(new LongArrayTag(new long[]{Long.MIN_VALUE, -100, 0, 100, Long.MAX_VALUE}), new LongArrayTag());
  }

  @Test
  void testLong() throws IOException {
    this.testWriteRead(new LongTag(10), new LongTag());
  }

  @Test
  void testShort() throws IOException {
    this.testWriteRead(new ShortTag((short) 12), new ShortTag());
  }

  @Test
  void testString() throws IOException {
    final StringTag a = new StringTag("Hello, world!");
    final StringTag b = new StringTag();
    this.writeRead(a, b);
    assertEquals(a, b);
  }

  private <T extends Tag> void testWriteRead(final T a, final T b) throws IOException {
    this.writeRead(a, b);
    assertEquals(a, b);
  }

  @SuppressWarnings("UnstableApiUsage")
  private void writeRead(final Tag a, final Tag b) throws IOException {
    final ByteArrayDataOutput output = ByteStreams.newDataOutput();
    a.write(TagTypeMaps.MINECRAFT, output);
    final ByteArrayDataInput input = ByteStreams.newDataInput(output.toByteArray());
    b.read(TagTypeMaps.MINECRAFT, input, 0);
  }
}
