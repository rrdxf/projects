package com.example.secondhand.mapper;

import com.example.secondhand.beans.ShopCart;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface ShopcartMapper {
    int InsertShopchar(String shopcartid,String userid,String goodid);
    List<ShopCart> findShopcartByid(String userid);
    int deletShopcart (String userid,String goodid);
}
