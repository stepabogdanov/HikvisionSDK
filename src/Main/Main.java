package Main;

import com.sun.jna.NativeLong;
import com.sun.jna.platform.win32.WinDef;

import javax.swing.*;
import java.util.logging.Level;

/**
 * Created by дом on 20.02.2018.
 */
public class Main {

    public static void main(String[] args) throws InterruptedException {
        Init init = new Init();
//        Window window = new Window();
        WinDef.HWND hwnd = new WinDef.HWND();
//        Init.logger.setLevel(Level.OFF);

//        window.getWindow();

//
        Init.init();
        Init.getSDKState();
        //176.226.154.133 user user-111
        NativeLong userId = Init.login("admin", "12345", "192.168.1.12", (short)8000);
        Thread.sleep(100);
        //Init.realPlay(window);


        System.out.println("Serial number is: " + Init.getSerialNumbre());

        Init.getSDKAbility();
        Init.logOut();
        Init.cleanup();


//        NativeLong cannel = new NativeLong(1);
//        init.downloadFileByTime(userId, cannel);




//        Init.initOld();

//        int i = 16546435;
//        System.out.println(Integer.parseInt("ff", 16));

    }

    public static class Window extends JLabel {
        Window() {
            JFrame frame = new JFrame("MyWindow");
            //frame.setLocation(100,100);
            frame.setBounds(20, 30, 500, 300);
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);
        }

    }

}
