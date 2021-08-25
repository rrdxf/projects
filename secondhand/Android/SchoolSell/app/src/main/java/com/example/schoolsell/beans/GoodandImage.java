package com.example.schoolsell.beans;

import java.util.List;

public class GoodandImage {

    private List<Image> imagelist;
    private String goodid;
    public void setImagelist(List<Image> imagelist) {
        this.imagelist = imagelist;
    }

    public List<Image> getImagelist() {
        return imagelist;
    }





    public void setGoodid(String goodid) {
        this.goodid = goodid;
    }



    public String getGoodid() {
        return goodid;
    }
}
