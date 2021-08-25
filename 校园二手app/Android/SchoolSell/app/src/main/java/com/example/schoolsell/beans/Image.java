package com.example.schoolsell.beans;

public class Image {
    String imgid;
    String imgsrc;
    String good_id;

    public void setGood_id(String good_id) {
        this.good_id = good_id;
    }

    public String getGood_id() {
        return good_id;
    }

    public String getImgid() {
        return imgid;
    }

    public String getImgsrc() {
        return imgsrc;
    }

    @Override
    public String toString() {
        return "Image{" +
                "imgid='" + imgid + '\'' +
                ", imgsrc='" + imgsrc + '\'' +
                '}';
    }

    public void setImgid(String imgid) {
        this.imgid = imgid;
    }

    public void setImgsrc(String imgsrc) {
        this.imgsrc = imgsrc;
    }

    public Image(String imgsrc) {

        this.imgsrc = imgsrc;
    }
    public Image(){}

}
