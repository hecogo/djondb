/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.util;

/**
 *
 * @author cross
 */
public class StringUtil {

    public static String replaceAll(String original, String replace, String replaceWith) {
        StringBuffer sb = new StringBuffer();
        final int replaceLength = replace.length();

        int index = 0;
        int lastIndex = 0;
        while ((index = original.indexOf(replace, lastIndex)) > -1) {
            char[] dest = new char[index - lastIndex];
            original.getChars(lastIndex, index, dest, 0);
            sb.append(dest, 0, dest.length);
            sb.append(replaceWith);
            index += replaceLength;
            lastIndex = index;
        }
        if (lastIndex < original.length()) {
            char[] dest = new char[original.length() - lastIndex];
            original.getChars(lastIndex, original.length(), dest, 0);
            sb.append(dest);
        }
        return sb.toString();
    }

}
