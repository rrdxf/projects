package com.example.schoolsell.beans;

import java.util.List;

public class Good {
    private String goodid;
    private String goodname;
    private String goodprice;
    private String goodexpression;
    private String ownerid;



    private List<Image> goodimgelist;
    private User owner;

    public Good(){

    }
    public Good(String goodid, String goodname, String goodprice, String goodexpression, String ownerid, List<Image> goodimgelist, User owner) {
        this.goodid = goodid;
        this.goodname = goodname;
        this.goodprice = goodprice;
        this.goodexpression = goodexpression;
        this.ownerid = ownerid;
        this.goodimgelist = goodimgelist;
        this.owner = owner;
    }

    public void setOwnerid(String ownerid) {
        this.ownerid = ownerid;
    }

    public String getOwnerid() {
        return ownerid;
    }

    @Override
    public String toString() {
        return "Good{" +
                "goodid='" + goodid + '\'' +
                ", goodname='" + goodname + '\'' +
                ", goodprice='" + goodprice + '\'' +
                ", goodexpression='" + goodexpression + '\'' +
                ", ownerid='" + ownerid + '\'' +
                ", goodimgelist=" + goodimgelist.toString() +
                ", owner=" + owner +
                '}';
    }

    public void setGoodid(String goodid) {
        this.goodid = goodid;
    }

    public void setGoodname(String goodname) {
        this.goodname = goodname;
    }

    public void setGoodprice(String goodprice) {
        this.goodprice = goodprice;
    }

    public void setGoodexpression(String goodexpression) {
        this.goodexpression = goodexpression;
    }

    public void setGoodimgelist(List<Image> goodimgelist) {
        this.goodimgelist = goodimgelist;
    }

    public void setOwner(User owner) {
        this.owner = owner;
    }

    public String getGoodid() {
        return goodid;
    }

    public String getGoodname() {
        return goodname;
    }

    public String getGoodprice() {
        return goodprice;
    }

    public String getGoodexpression() {
        return goodexpression;
    }

    public List<Image> getGoodimgelist() {
        return goodimgelist;
    }

    public User getOwner() {
        return owner;
    }
}
