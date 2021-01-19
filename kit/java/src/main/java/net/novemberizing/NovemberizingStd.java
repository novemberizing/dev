package net.novemberizing;

import com.google.gson.JsonPrimitive;

public class NovemberizingStd {
    // public static final NovemberizingJson json = new NovemberizingJson();

    public final NovemberizingJson json = new NovemberizingJson();

    public void out(String string) {
        System.out.println(string);
    }

    public void err(String string) {
        System.err.println(string);
    }

    public static void main(String[] args) {
        NovemberizingStd novemberizing = new NovemberizingStd();

        novemberizing.out(novemberizing.json.string(new JsonPrimitive("hello world")));
        novemberizing.err(novemberizing.json.string(new JsonPrimitive("hello world")));

        // novemberizing.json
    }
}
