#ifndef DATE_TIME_GREGORIAN_IO_HPP__
#define DATE_TIME_GREGORIAN_IO_HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/date_facet.hpp"
#include <iostream>
#include <locale>

namespace boost {
namespace gregorian {


  typedef boost::date_time::period_formatter<wchar_t> wperiod_formatter;
  typedef boost::date_time::period_formatter<char>    period_formatter;
  
  typedef boost::date_time::date_facet<date,wchar_t> wdate_facet;
  typedef boost::date_time::date_facet<date,char>    date_facet;

  typedef boost::date_time::period_parser<date,char>       period_parser;
  typedef boost::date_time::period_parser<date,wchar_t>    wperiod_parser;
    
  typedef boost::date_time::special_values_parser<date,char> special_values_parser; 
  typedef boost::date_time::special_values_parser<date,wchar_t> wspecial_values_parser; 
  
  typedef boost::date_time::date_input_facet<date,char>    date_input_facet;
  typedef boost::date_time::date_input_facet<date,wchar_t> wdate_input_facet;

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date& d) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), d);
    else {
      //instantiate a custom facet for dealing with dates since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every date
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues at some later point.  With the default settings
      //for the facet the resulting format will be the same as the
      //std::time_facet settings.
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), d);
    }
    return os;
  }

  //! input operator for date
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, date& d)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, d);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, d);
    }
    return is;
  }

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date_duration& dd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), dd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), dd);

    }
    return os;
  }

  //! input operator for date_duration
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, date_duration& dd)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, dd);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, dd);
    }
    return is;
  }

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date_period& dp) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), dp);
    else {
      //instantiate a custom facet for dealing with date periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues at some later point.  With the default settings
      //for the facet the resulting format will be the same as the
      //std::time_facet settings.
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), dp);

    }
    return os;
  }

  //! input operator for date_period 
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, date_period& dp)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, dp);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, dp);
    }
    return is;
  }

  /********** small gregorian types **********/
  
  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::greg_month& gm) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), gm);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();//-> 10/1074199752/32 because year & day not initialized in put(...)
      //custom_date_facet* f = new custom_date_facet("%B");
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), gm);
    }
    return os;
  }

  //! input operator for greg_month
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, greg_month& m)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, m);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, m);
    }
    return is;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::greg_weekday& gw) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), gw);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), gw);
    }
    return os;
  }
 
  //! input operator for greg_weekday
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, greg_weekday& wd)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, wd);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, wd);
    }
    return is;
  }

  //NOTE: output operator for greg_day was not necessary

  //! input operator for greg_day
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, greg_day& gd)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, gd);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, gd);
    }
    return is;
  }

  //NOTE: output operator for greg_year was not necessary

  //! input operator for greg_year
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, greg_year& gy)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, gy);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, gy);
    }
    return is;
  }

  /********** date generator types **********/
  
  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::partial_date& pd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), pd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), pd);
    }
    return os;
  }

  //! input operator for partial_date
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, partial_date& pd)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, pd);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, pd);
    }
    return is;
  }

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::nth_day_of_the_week_in_month& nkd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), nkd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), nkd);
    }
    return os;
  }

  //! input operator for nth_day_of_the_week_in_month
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, 
             nth_day_of_the_week_in_month& nday)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, nday);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, nday);
    }
    return is;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_in_month& fkd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), fkd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), fkd);
    }
    return os;
  }

  //! input operator for first_day_of_the_week_in_month
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, 
             first_day_of_the_week_in_month& fkd)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, fkd);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, fkd);
    }
    return is;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::last_day_of_the_week_in_month& lkd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), lkd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), lkd);
    }
    return os;
  }

  //! input operator for last_day_of_the_week_in_month
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, 
             last_day_of_the_week_in_month& lkd)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, lkd);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, lkd);
    }
    return is;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_after& fda) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc())) {
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), fda);
    } 
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), fda);
    }
    return os;
  }

  //! input operator for first_day_of_the_week_after
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, 
             first_day_of_the_week_after& fka)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, fka);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, fka);
    }
    return is;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_before& fdb) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc())) {
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), fdb);
    }
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), fdb);
    }
    return os;
  }

  //! input operator for first_day_of_the_week_before
  template <class charT, class traits>
  inline
  std::basic_istream<charT, traits>&
  operator>>(std::basic_istream<charT, traits>& is, 
             first_day_of_the_week_before& fkb)
  {
    typedef typename date_time::date_input_facet<date, charT> date_input_facet;
    std::istreambuf_iterator<charT,traits> sit(is), str_end;
    if(std::has_facet<date_input_facet>(is.getloc())) {
      std::use_facet<date_input_facet>(is.getloc()).get(sit, str_end, is, fkb);
    }
    else {
      date_input_facet* f = new date_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, fkb);
    }
    return is;
  }

  
} } // namespaces

#endif // DATE_TIME_GREGORIAN_IO_HPP__
