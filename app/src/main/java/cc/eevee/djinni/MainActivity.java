package cc.eevee.djinni;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Html;
import android.util.Log;
import android.widget.TextView;

import java.io.File;
import java.util.Locale;

import cc.eevee.djinni.leveldb.Leveldb;
import cc.eevee.djinni.leveldb.WriteBatch;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    private TextEditor mTextEditor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextEditor = new TextEditor(findViewById(R.id.text));

        testLeveldb();
    }

    private void testLeveldb() {
        TextEditor editor = mTextEditor;
        editor.appendLine(Html.fromHtml("<font color='magenta'>testLeveldb</color>"));

        File dbPath = new File(getFilesDir(), "leveldb");
        Log.i(TAG, dbPath.getPath());

        Leveldb db = Leveldb.create();
        db.open(dbPath.getPath());

        db.put("key", "string@leveldb");

        WriteBatch batch = WriteBatch.create();
        batch.put("batch", "batch@leveldb");
        db.write(batch);

        editor.appendLine(db.get("key"));
        editor.appendLine(db.get("batch"));

        db.close();
    }

    private static class TextEditor {

        private TextView mTextView;

        public TextEditor(TextView textView) {
            mTextView = textView;
        }

        public TextEditor append(CharSequence text) {
            mTextView.append(text);
            return this;
        }

        public TextEditor append(CharSequence format, Object... args) {
            mTextView.append(String.format(Locale.getDefault(), format.toString(), args));
            return this;
        }

        public TextEditor newline() {
            return append("\n");
        }

        public TextEditor appendLine(CharSequence text) {
            return append(text).newline();
        }

        public TextEditor appendLine(CharSequence format, Object... args) {
            return append(format, args).newline();
        }
    }
}
