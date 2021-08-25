package com.example.secondhand.controller;

import com.example.secondhand.beans.ShopCart;
import com.example.secondhand.mapper.ShopcartMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/shopcart")
public class ShopcartController {
    @Autowired
    ShopcartMapper shopcartMapper;

    @RequestMapping("/loadshopcart")
    public List<ShopCart> loadshopcart(String userid){
        System.out.println(userid);
        List<ShopCart> shopCartList=shopcartMapper.findShopcartByid(userid);
        return shopCartList;
    }

    @RequestMapping("/addgoodtocart")
    public int addgoodtocart(String goodid,String userid){
        System.out.println("userid"+userid);
        System.out.println("goodid"+goodid);
        return shopcartMapper.InsertShopchar(Integer.toString((int)(Math.random()*(1000-1)+1)),userid,goodid);
    }
    @RequestMapping("/deletgoodtocart")
    public int deletgoodtocart(String userid,String goodid){
        System.out.println("userid"+userid);
        System.out.println("goodid"+goodid);
        return shopcartMapper.deletShopcart(userid,goodid);
    }


}
