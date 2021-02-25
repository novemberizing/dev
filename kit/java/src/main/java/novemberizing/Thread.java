package novemberizing;

public class Thread {
    public interface Func { void call(novemberizing.Thread thread); }

    protected java.lang.Thread handle = null;
    protected Func func               = null;
    protected Integer status          = null;
    protected Func cancel             = null;


}
