package com.example.secondhand.mapper;

import com.example.secondhand.beans.Good;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

@Mapper
public interface GoodMapper {
    int insertGood(Good good);
    Good selectGoodbyid(String Goodid);
    List<Good> selectGoodbyuserid(String Userid);
    List<Good> selectGoodByName(String Goodname);
    List<Good> selectAllGood();
    int deletGood(String goodid);
}
