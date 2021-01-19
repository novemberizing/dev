package net.novemberizing;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;
import com.google.gson.JsonNull;
import com.google.gson.JsonPrimitive;

public class NovemberizingJson {
//    private static final Gson gson;
//    private static final Gson pretty;
//
//    static {
//        GsonBuilder builder = new GsonBuilder();
//        builder.disableHtmlEscaping();
//
//        gson = builder.create();
//
//        builder = new GsonBuilder();
//        builder.disableHtmlEscaping();
//        builder.setPrettyPrinting();
//        pretty = builder.create();
//    }
//
//    public static String string(JsonElement element) {
//        if(element != null) {
//
//        }
//        return null;
//    }
//
//    public static void main(String[] args) {
//
//        System.out.println("hello");
//    }
//
//
//
    // private Gson example;
    // Gson
    // private static final Gson

    private Gson gson;

    public NovemberizingJson(Gson gson) {
        this.gson = gson;
    }

    public NovemberizingJson() {
        GsonBuilder builder = new GsonBuilder();
        builder.disableHtmlEscaping();
        builder.setPrettyPrinting();
        this.gson = builder.create();
    }

    /**
     * {@link JsonElement} 를 문자열로 변환합니다.
     *
     * {@code element} 파라미터가 {@link JsonNull} 이거나 {@code null} 인 경우는 {@code null} 을 리턴히고,
     * {@link JsonPrimitive} 가 아닌 경우는 예외를 생성합니다.
     *
     *
     * @param element   | {@link JsonElement} | 변환하고자 하는 입력 값입니다. |
     * @return          | {@link String}      | 변환된 문자열을 리턴합니다. |
     */
    public String string(JsonElement element) {
        if(element != null && !element.isJsonNull()) {
            if(element.isJsonPrimitive()) {
                return this.string(element.getAsJsonPrimitive());
            }
            throw new RuntimeException();
        }
        return null;
    }

    /**
     * {@link JsonPrimitive} 를 {@link String} 으로 변환합니다.
     *
     *
     *
     * @param primitive     | {@link JsonPrimitive} | 변환하거자 하는 파라미터 |
     * @return              | {@link String}        | 변환된 입력 값 |
     */
    public String string(JsonPrimitive primitive) {
        if(primitive != null && !primitive.isJsonNull()) {
            if(primitive.isString()) {
                return primitive.getAsString();
            }
            throw new RuntimeException();
        }
        return null;
    }
}
