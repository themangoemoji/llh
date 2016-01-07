package edu.msu.wrigh517.llh;

import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.net.Uri;
import android.os.Looper;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class LLHActivity extends AppCompatActivity {


    private static final String MIMETYPE_TEXT_PLAIN = "";
    private String text_field = "";
    private String textFromClipboard = "";

    private char[][] letters =
            {{'A', 'B', 'C', 'D'},
            {'E', 'F', 'G', 'H'},
            {'I', 'J', 'K', 'L'}};



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_llh);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_llh, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }


    public void selectKey(int row, int column) {
        char letter = letters[row][column];
        Log.i("Letter: ", String.valueOf(letter));
        enterLetter(letter);
    }

    private void enterLetter(char letter) {

        // If we have already seen this before, we have to recognize that

        text_field += letter;
        UpdateTextView();



    }

    private void UpdateTextView() {
        ((TextView) findViewById(R.id.textView)).setText(text_field);
    }

    public void OnPaste(View view) {

        /*
        * Handle pasting from Clipboard to textview
         */
        ClipboardManager clipboard = (ClipboardManager) getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData.Item item = clipboard.getPrimaryClip().getItemAt(0);
        // Gets the clipboard as text.
        CharSequence pasteData = item.getText();
        // If the string contains data, then the paste operation is done
        if (pasteData != null) {
//            ClipData.Item pasteData = clipboard.getPrimaryClip().getItemAt(0);

            Log.i("Clip: ", pasteData.toString());

            textFromClipBoard  = pasteData.toString();

            text_field = textFromClipBoard;

            UpdateTextView();
            Toast.makeText(view.getContext(),
                    R.string.paste_success,
                    Toast.LENGTH_SHORT).show();
            return;

// The clipboard does not contain text. If it contains a URI, attempts to get data from it
        } else {
            Uri pasteUri = item.getUri();

            // If the URI contains something, try to get text from it
            if (pasteUri != null) {

                // calls a routine to resolve the URI and get data from it. This routine is not
                // presented here.
//                pasteData = resolveUri(Uri);
                return;
            } else {

                // Something is wrong. The MIME type was plain text, but the clipboard does not contain either
                // text or a Uri. Report an error.
                Log.i("Clipboard contains an invalid data type", "YO");
                return;
            }
        }

        new Thread(new Runnable() {

            @Override
            public void run() {
                Cloud cloud = new Cloud();
                final boolean ok = cloud.saveToCloud(textFromClipboard);
                if(!ok) {
                    /*
                     * If we fail to save, display a toast
                     */
                    // Please fill this in...
                    Looper.prepare();
                    Toast.makeText(view.getContext(),
                            R.string.save_fail,
                            Toast.LENGTH_SHORT).show();

                }
            }
        }).start();

    }

    public void OnClear(View view) {
        text_field = "";
        ((TextView) findViewById(R.id.textView)).setText(text_field);
    }

}
