package com.example.schoolsell.entity;

import android.graphics.Bitmap;

import java.io.File;

public class LoadFileVo {
    File file;
    int pg;
    boolean isUpload=false;
    Bitmap bitmap;

    public File getFile() {
        return file;
    }

    public int getPg() {
        return pg;
    }

    public boolean isUpload() {
        return isUpload;
    }

    public Bitmap getBitmap() {
        return bitmap;
    }

    public void setFile(File file) {
        this.file = file;
    }

    public void setPg(int pg) {
        this.pg = pg;
    }

    public void setUpload(boolean upload) {
        isUpload = upload;
    }

    public void setBitmap(Bitmap bitmap) {
        this.bitmap = bitmap;
    }

    public LoadFileVo(){

    }

    public LoadFileVo(File file, int pg, boolean isUpload, Bitmap bitmap) {
        this.file = file;
        this.pg = pg;
        this.isUpload = isUpload;
        this.bitmap = bitmap;
    }

    public LoadFileVo(File file, int pg) {
        this.file = file;
        this.pg = pg;
    }
}
