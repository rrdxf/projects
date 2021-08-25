package com.example.secondhand.beans;

import java.util.List;

public class Good {
    private String Goodid;
    private String Goodname;
    private String Goodprice;
    private String Goodexpression;
    private String ownerid;
    private String shopcart_id;
    public Good(){

    }
    public Good(String goodid, String goodname, String goodprice, String goodexpression, String ownerid) {
        Goodid = goodid;
        Goodname = goodname;
        Goodprice = goodprice;
        Goodexpression = goodexpression;
        this.ownerid = ownerid;
    }

    private List<Image> Goodimgelist;
    private User owner;

    public void setOwnerid(String ownerid) {
        this.ownerid = ownerid;
    }

    public String getOwnerid() {
        return ownerid;
    }

    @Override
    public String toString() {
        return "Good{" +
                "Goodid='" + Goodid + '\'' +
                ", Goodname='" + Goodname + '\'' +
                ", Goodprice='" + Goodprice + '\'' +
                ", Goodexpression='" + Goodexpression + '\'' +

                ", owner=" + owner +
                '}';
    }
    public List<Image> getGoodimgelist() {
        return Goodimgelist;
    }

    public void setGoodimgelist(List<Image> goodimgelist) {
        Goodimgelist = goodimgelist;
    }
    public User getOwner() {
        return owner;
    }

    public void setOwner(User owner) {
        this.owner = owner;
    }




    public void setGoodid(String goodid) {
        Goodid = goodid;
    }

    public void setGoodname(String goodname) {
        Goodname = goodname;
    }

    public void setGoodprice(String goodprice) {
        Goodprice = goodprice;
    }

    public void setGoodexpression(String goodexpression) {
        Goodexpression = goodexpression;
    }

    public String getGoodid() {
        return Goodid;
    }

    public String getGoodname() {
        return Goodname;
    }

    public String getGoodprice() {
        return Goodprice;
    }

    public String getGoodexpression() {
        return Goodexpression;
    }


}
