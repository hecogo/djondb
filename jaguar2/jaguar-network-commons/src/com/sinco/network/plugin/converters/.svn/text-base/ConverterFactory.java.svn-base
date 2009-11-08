/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network.plugin.converters;

import com.sinco.cache.CacheFactory;
import com.sinco.cache.CacheGroup;
import com.sinco.network.plugin.Converter;

/**
 *
 * @author cross
 */
public class ConverterFactory {
    private static final String CACHEKEY = "CONVERTER";

    public static Converter getConverter(Class clazz) {
        CacheGroup globalCache = CacheFactory.getGlobalCache(CACHEKEY);
        Converter result = (Converter) globalCache.get(clazz.getName());
        if (result != null) {
            return result;
        } else {
            if (clazz.getName().equals("java.lang.Integer")) {
                result = new PrimitiveConverter(PrimitiveConverter.Primitive.INTEGER);
            } else if (clazz.getName().equals("java.lang.String")) {
                result = new PrimitiveConverter(PrimitiveConverter.Primitive.STRING);
            } else if (clazz.getName().equals("java.lang.Double")) {
                result = new PrimitiveConverter(PrimitiveConverter.Primitive.DOUBLE);
            } else if (clazz.getName().equals("java.util.Date")) {
                result = new PrimitiveConverter(PrimitiveConverter.Primitive.DATE);
            } else {
                throw new IllegalArgumentException(String.format("The class %s does not have a valid converter", clazz.getName()));
            }
            globalCache.add(clazz.getName(), result);
            return result;
        }
    }
}
