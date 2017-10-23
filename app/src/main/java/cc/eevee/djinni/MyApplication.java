package cc.eevee.djinni;

import android.app.Application;

public class MyApplication extends Application {

    static {
        try {
            System.loadLibrary("leveldb_jni");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("LevelDB library failed to load.\n" + e);
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();
    }
}
