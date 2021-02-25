package novemberizing;

public interface Sync {
    class Type {
        public static final int MUTEX = 0x00000000;
        public static final int SPINLOCK = 0x00000001;
        public static final int DEFAULT = Type.MUTEX;
    }
    int lock();
    int unlock();
    int wait(long second, long nanosecond);
    int wakeup(boolean all);
}
