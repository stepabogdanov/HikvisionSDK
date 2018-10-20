package Main;

import com.sun.jna.NativeLong;

import java.util.logging.Level;

/**
 * Created by дом on 20.02.2018.
 */
public class Main {

    public static void main(String[] args) throws InterruptedException {
        Init init = new Init();

        Init.logger.setLevel(Level.ALL);



/*
        init.init();
        init.getSDKState();
        NativeLong userId = init.login("admin", "12345", "192.168.1.23", (short)8000);
        init.getSDKAbility();
        NativeLong cannel = new NativeLong(1);
        init.downloadFileByTime(userId, cannel);



        init.cleanup();

*/


        Init.initOld();

//        int i = 16546435;
//        System.out.println(Integer.parseInt("ff", 16));

    }

}
