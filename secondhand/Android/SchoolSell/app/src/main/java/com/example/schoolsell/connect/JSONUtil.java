package com.example.schoolsell.connect;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonSyntaxException;

import java.io.StringWriter;
import java.lang.reflect.Type;
import java.util.Date;
import java.util.List;

public class JSONUtil {
    private static Gson gson;
    static {
        // 创建gson对象构建器
        GsonBuilder gsonBuilder = new GsonBuilder().setDateFormat("yyyy-MM-dd hh:mm:ss");
        // 实现将long 类型的日期格式转换为国际标准格式
        gsonBuilder.registerTypeAdapter(Date.class, (JsonDeserializer<Date>) (json, typeOfT, context) -> new Date(json.getAsJsonPrimitive().getAsLong()));
        gson = gsonBuilder.create();
    }

    public static String toJsonWithAnnotation(Object src, Type classOfT) throws JsonSyntaxException {
        return new GsonBuilder().excludeFieldsWithoutExposeAnnotation().create()
                .toJson(src, classOfT);
    }

    public static <T> T fromJson(String json, Type classOfT) throws JsonSyntaxException {
        return gson.fromJson(json, classOfT);
    }


    public static <T> List<T> fromJsons(String json, Type classOfT) throws JsonSyntaxException {
        return gson.fromJson(json, classOfT);
    }

    public static String toJson(Object src, Type typeOfSrc) {
        StringWriter writer = new StringWriter();
        gson.toJson(src, typeOfSrc, writer);
        return writer.toString();
    }
}