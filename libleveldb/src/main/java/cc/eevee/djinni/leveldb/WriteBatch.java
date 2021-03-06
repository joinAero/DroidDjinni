// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from leveldb.idl

package cc.eevee.djinni.leveldb;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import java.util.concurrent.atomic.AtomicBoolean;

public abstract class WriteBatch {
    public abstract void put(@NonNull String key, @NonNull String value);

    public abstract void del(@NonNull String key);

    public abstract void clear();

    @Nullable
    public static native WriteBatch create();

    private static final class CppProxy extends WriteBatch
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            destroy();
            super.finalize();
        }

        @Override
        public void put(String key, String value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_put(this.nativeRef, key, value);
        }
        private native void native_put(long _nativeRef, String key, String value);

        @Override
        public void del(String key)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_del(this.nativeRef, key);
        }
        private native void native_del(long _nativeRef, String key);

        @Override
        public void clear()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_clear(this.nativeRef);
        }
        private native void native_clear(long _nativeRef);
    }
}
