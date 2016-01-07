package edu.msu.wrigh517.llh;

import android.util.Log;
import android.util.Xml;
import android.view.View;
import android.widget.TextView;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlSerializer;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;

/**
 * Created by mhw on 1/2/16.
 */
public class Cloud {

    String input = "";

    LLHActivity llhActivity = new LLHActivity();

    private static View llhView;

    private static final String SAVE_URL = "http://webdev.cse.msu.edu/~wrigh517/llh/llh-save.php";


    public void Lookup() {
        // Get the string from the box to lookup
        new Thread(new Runnable() {
            @Override
            public void run() {
                String returnText = getMatch();
                Log.i("returnText", returnText);
            }
        }).start();
    }

    public String getMatch() {
        // The input is set upon lookup at enterletter
        return "Yo, Match Dawg " + input;
    }


    // This is used by LLHActivity
    public void setInput(String text_field) {
        input = text_field;
    }

    public boolean saveToCloud(String llhURL) {
        llhURL = llhURL.trim();
        if(llhURL.length() == 0) {
            return false;
        }

         /*
         * Convert the XML into HTTP POST data
         */
        String postDataStr;
//        try {
//            postDataStr = "xml=" + URLEncoder.encode(xmlStr, "UTF-8");
//        } catch (UnsupportedEncodingException e) {
//            return false;
//        }

        /*
         * Send the data to the server
         */
        byte[] postData = postDataStr.getBytes();

        InputStream stream = null;
        try {
            URL url = new URL(SAVE_URL);

            HttpURLConnection conn = (HttpURLConnection) url.openConnection();

            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Length", Integer.toString(postData.length));
            conn.setUseCaches(false);

            OutputStream out = conn.getOutputStream();
            out.write(postData);
            out.close();

            int responseCode = conn.getResponseCode();
            if(responseCode != HttpURLConnection.HTTP_OK) {
                return false;
            }
            stream = conn.getInputStream();

            /**
             * Create an XML parser for the result
             */
            try {
                XmlPullParser xmlR = Xml.newPullParser();
                xmlR.setInput(stream, UTF8);

                xmlR.nextTag();      // Advance to first tag
                xmlR.require(XmlPullParser.START_TAG, null, "hatter");

                String status = xmlR.getAttributeValue(null, "status");
                if(status.equals("no")) {
                    stream = null;
                    return false;
                }

                // We are done
            } catch(XmlPullParserException ex) {
                return false;
            } catch(IOException ex) {
                return false;
            }
//            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
//            String line;
//            while ((line = reader.readLine()) != null) {
//                Log.i("hatter", line);
//            }

        } catch (MalformedURLException e) {
            return false;
        } catch (IOException ex) {
            return false;
        } finally {
            if(stream != null) {
                try {
                    stream.close();
                } catch(IOException ex) {
                    // Fail silently
                }
            }
        }
        return true;
    }


}
