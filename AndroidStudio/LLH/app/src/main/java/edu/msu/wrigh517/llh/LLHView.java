package edu.msu.wrigh517.llh;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

/**
 * Created by mhw on 11/6/15.
 */
public class LLHView extends View {
    /**
     * The image bitmap.
     */
    private Bitmap imageBitmap = null;

    private float imageScale = 1;

    private float marginLeft = 0;

    private float marginTop = 0;

    public LLHView(Context context) {
        super(context);
        init();
    }

    public LLHView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public LLHView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        init();
    }

    public void init() {
        imageBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.keyboard);
    }

    /* (non-Javadoc)
     * @see android.view.View#onDraw(android.graphics.Canvas)
     */
    @Override
    protected void onDraw(Canvas canvas) {
        // TODO Auto-generated method stub
        super.onDraw(canvas);

        if(imageBitmap == null) {
            return;
        }

        float wid = canvas.getWidth();
        float hit = canvas.getHeight();

        // What would be the scale to draw the where it fits both
        // horizontally and vertically?
        float scaleH = wid / imageBitmap.getWidth();
        float scaleV = hit / imageBitmap.getHeight();

        // Use the lesser of the two
        imageScale = scaleH < scaleV ? scaleH : scaleV;

        // What is the scaled image size?
        float iWid = imageScale * imageBitmap.getWidth();
        float iHit = imageScale * imageBitmap.getHeight();

        // Determine the top and left margins to center
        marginLeft = (wid - iWid) / 2;
        marginTop = (hit - iHit) / 2;

        // And draw the bitmap
        canvas.save();
        canvas.translate(marginLeft,  marginTop);
        canvas.scale(imageScale, imageScale);
        canvas.drawBitmap(imageBitmap, 0, 0, null);
        canvas.restore();

    }

    /* (non-Javadoc)
     * @see android.view.View#onTouchEvent(android.view.MotionEvent)
     */
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        switch(event.getActionMasked()) {
            case MotionEvent.ACTION_DOWN:
                touched(event.getX(0), event.getY(0));
                break;
        }
        // TODO Auto-generated method stub
        return super.onTouchEvent(event);
    }

    private void touched(float x, float y) {
        y -= marginTop;
        x -= marginLeft;
        x /= imageScale;
        y /= imageScale;

        if(x >= 0 && x < imageBitmap.getWidth() &&
                y >= 0 && y < imageBitmap.getHeight()) {
            float keyWidth = (imageBitmap.getWidth() / 4);
            int column = (int) (x / keyWidth);
            float keyHeight = (imageBitmap.getHeight() / 3);
            int row = (int) (y / keyHeight);
            String rowcol = "Row: ";
            rowcol += row + 1;
            rowcol += ", Col: ";
            rowcol += column + 1;
            Log.i("Column", rowcol);
            int letterpos = imageBitmap.getPixel((int) x, (int) y);
            LLHActivity activity = (LLHActivity)getContext();
            activity.selectKey(row, column);
        }
    }


}
