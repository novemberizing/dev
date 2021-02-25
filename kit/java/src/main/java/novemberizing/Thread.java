package novemberizing;

public class Thread {
    public static class Status {
        public static final int VOID = 0x00000000;
        public static final int ON   = 0x00000001;
    }
    public interface Func { void call(novemberizing.Thread thread); }

    protected java.lang.Thread handle = null;
    protected Func func;
    protected Integer status;
    protected Func cancel             = null;

    public void run() {

    }

    public Thread(Func func) {
        this.func = func;
        this.status = Thread.Status.VOID;
    }
}
