package com.example.secondhand.beans;

public class Image {
    String imgid;
    String good_id;
    String imgsrc;


    public Image(String imgsrc) {
        this.imgsrc = imgsrc;
    }


    public Image(){

    }
    public Image(String imgsrc,String good_id){
        this.imgsrc=imgsrc;
        this.good_id=good_id;
    }
    public Image(String imgid, String imgsrc, String good_id) {
        this.imgid = imgid;
        this.good_id = good_id;
        this.imgsrc = imgsrc;
    }

    public void setGood_id(String good_id) {
        this.good_id = good_id;
    }

    public String getGood_id() {
        return good_id;
    }


    @Override
    public String toString() {
        return "Image{" +
                "imgid='" + imgid + '\'' +
                ", imgsrc='" + imgsrc + '\'' +
                '}';
    }




    public String getImgid() {
        return imgid;
    }

    public String getImgsrc() {
        return imgsrc;
    }

    public void setImgid(String imgid) {
        this.imgid = imgid;
    }

    public void setImgsrc(String imgsrc) {
        this.imgsrc = imgsrc;
    }




}
