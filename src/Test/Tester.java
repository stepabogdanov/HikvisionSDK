package Test;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

/**
 * Created by дом on 20.02.2018.
 */
public class Tester {
    private static Kernel32 kernel32 = (Kernel32) Native.loadLibrary("C:\\windows\\system32\\kernel32", Kernel32.class);
    private static User32 user32 = (User32) Native.loadLibrary("c:\\windows\\system32\\user32", User32.class);

    public interface Kernel32 extends Library {
        boolean Beep (int frequency, int duration);
    }

    public interface User32 extends Library {
        Pointer GetDesktopWindow();
    }


}
