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

public class TagTypeMaps {
  public static final TagTypeMap MINECRAFT = new TagTypeMap() {
    @Override
    public byte getId(TagType type) {
      switch(type) {
        case END:
          return 0;
        case BYTE:
          return 1;
        case SHORT:
          return 2;
        case INT:
          return 3;
        case LONG:
          return 4;
        case FLOAT:
          return 5;
        case DOUBLE:
          return 6;
        case BYTE_ARRAY:
          return 7;
        case STRING:
          return 8;
        case LIST:
          return 9;
        case COMPOUND:
          return 10;
        case INT_ARRAY:
          return 11;
        case LONG_ARRAY:
          return 12;
        default:
          throw new IllegalArgumentException("Unsupported tag type " + type);
      }
    }

    @Override
    public TagType fromId(int id) {
      switch(id) {
        case 0:
          return TagType.END;
        case 1:
          return TagType.BYTE;
        case 2:
          return TagType.SHORT;
        case 3:
          return TagType.INT;
        case 4:
          return TagType.LONG;
        case 5:
          return TagType.FLOAT;
        case 6:
          return TagType.DOUBLE;
        case 7:
          return TagType.BYTE_ARRAY;
        case 8:
          return TagType.STRING;
        case 9:
          return TagType.LIST;
        case 10:
          return TagType.COMPOUND;
        case 11:
          return TagType.INT_ARRAY;
        case 12:
          return TagType.LONG_ARRAY;
        default:
          throw new IllegalArgumentException("Unsupported tag type " + id);
      }
    }
  };

  /**
   * Robinton's cubic chunks mod from 2011 modified the NBT format to have short arrays.
   * Later, Mojang introduced long arrays with the same ID.
   */
  public static final TagTypeMap ROBINTON = new TagTypeMap() {
    @Override
    public byte getId(TagType type) {
      switch(type) {
        case END:
          return 0;
        case BYTE:
          return 1;
        case SHORT:
          return 2;
        case INT:
          return 3;
        case LONG:
          return 4;
        case FLOAT:
          return 5;
        case DOUBLE:
          return 6;
        case BYTE_ARRAY:
          return 7;
        case STRING:
          return 8;
        case LIST:
          return 9;
        case COMPOUND:
          return 10;
        case INT_ARRAY:
          return 11;
        case SHORT_ARRAY:
          return 12;
        default:
          throw new IllegalArgumentException("Unsupported tag type " + type);
      }
    }

    @Override
    public TagType fromId(int id) {
      switch(id) {
        case 0:
          return TagType.END;
        case 1:
          return TagType.BYTE;
        case 2:
          return TagType.SHORT;
        case 3:
          return TagType.INT;
        case 4:
          return TagType.LONG;
        case 5:
          return TagType.FLOAT;
        case 6:
          return TagType.DOUBLE;
        case 7:
          return TagType.BYTE_ARRAY;
        case 8:
          return TagType.STRING;
        case 9:
          return TagType.LIST;
        case 10:
          return TagType.COMPOUND;
        case 11:
          return TagType.INT_ARRAY;
        case 12:
          return TagType.SHORT_ARRAY;
        default:
          throw new IllegalArgumentException("Unsupported tag type " + id);
      }
    }
  };
}
