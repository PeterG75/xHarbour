/*
 * $Id: zipcollections.h 10235 2018-06-08 16:32:49Z enricomaria $
 */

////////////////////////////////////////////////////////////////////////////////
// $RCSfile: ZipCollections.h,v $
// $Revision: 10235 $ $Name:  $
// $Date: 2018-06-08 16:32:49 +0000 (Fri, 08 Jun 2018) $ $Author: enricomaria $
////////////////////////////////////////////////////////////////////////////////
// This source file is part of the ZipArchive library source distribution and
// is Copyrighted 2000-2005 by Tadeusz Dracz (http://www.artpol-software.com/)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// For the licensing details see the file License.txt
////////////////////////////////////////////////////////////////////////////////

#ifndef ZIPCOLLECTIONS_DOT_H
#define ZIPCOLLECTIONS_DOT_H

#if _MSC_VER > 1000
        #pragma warning( push, 3 )        // STL "requirements"
        #pragma warning (disable : 4284)  //return type for 'identifier::operator >' is not a UDT or reference to a UDT. Will produce errors if applied using infix notation
        #pragma warning (disable : 4018)  //'expression' : signed/unsigned mismatch
#endif

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>

#include "zipstring.h"
#include "ZipExport.h"

template<class TYPE>
class CZipArray : private std::vector<TYPE>
{
public:
typedef typename std::vector<TYPE>::iterator iterator;
typedef typename std::vector<TYPE> inherited;
protected:
iterator GetIterFromIndex( int uIndex )
{
   iterator iter = this->begin();

   iter += uIndex;
   //	int t = 0; while (t != uIndex) {iter++;t++;}
   return iter;
}
public:
void Sort( bool bAscending )
{
   if( bAscending )
      std::sort( this->begin(), this->end(), std::less<TYPE> () );
   else
      std::sort( this->begin(), this->end(), std::greater<TYPE> () );
}
int GetSize() const
{
   return ( int ) this->size();
}
int GetUpperBound() const
{
   return this->size() - 1;
}
int Add( const TYPE&x )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
      this->push_back( x );
   #else
      push_back( x );
   #endif   
    return GetUpperBound();
}
void RemoveAll()
{
   this->clear();
}
void RemoveAt( int uIndex )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
      this->erase( GetIterFromIndex( uIndex ) );
   #else
      erase( GetIterFromIndex( uIndex ) );
   #endif   
}
void InsertAt( int uIndex, const TYPE&x )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
      this->insert( GetIterFromIndex( uIndex ), x );
   #else
      insert( GetIterFromIndex( uIndex ), x );
   #endif   
}
#ifndef _MSC_VER
TYPE&operator[]( int iIndex )
{
   return inherited::operator[]( iIndex );
}
TYPE operator[]( int iIndex ) const
{
   return inherited::operator[]( iIndex );
}
#else
using inherited::operator[];
#endif
};


typedef CZipArray<CZipString> CZipStringArray;
typedef CZipArray<WORD> CZipWordArray;


template<class TYPE>
class ZIP_API CZipPtrList : private std::list<TYPE>
{

public:
typedef typename std::list<TYPE>::iterator iterator;
typedef typename std::list<TYPE>::const_iterator const_iterator;
int GetCount() const
{
   return this->size();
}
void AddTail( const TYPE&x )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
      this->push_back( x );
   #else	
      push_back( x );
   #endif
}
void AddHead( const TYPE&x )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
      this->push_front( x );
   #else
      push_front( x );
   #endif   
}
void RemoveHead()
{
   this->pop_front();
}
void RemoveTail()
{
   this->pop_back();
}
void RemoveAll()
{
   this->clear();
}
TYPE&GetHead()
{
   return this->front();
}
TYPE GetHead() const
{
   return this->front();
}
TYPE&GetTail()
{
   return this->back();
}
TYPE GetTail() const
{
   return this->back();
}
iterator GetHeadPosition()
{
   return this->begin();
}
const_iterator GetHeadPosition() const
{
   return this->begin();
}
iterator GetTailPosition()
{
   return this->back();
}
TYPE&GetNext( iterator&pos )
{
   return *pos++;
}
const TYPE GetNext( const_iterator&pos ) const
{
   return *pos++;
}
TYPE&GetPrev( iterator&pos )
{
   return *pos--;
}
TYPE GetPrev( iterator&pos ) const
{
   return *pos--;
}
iterator Find( TYPE&x )
{
   return std::find( this->begin(), this->end(), x );
}
void RemoveAt( iterator&pos )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
      this->erase( pos );
   #else
      erase( pos );
   #endif
}
bool IteratorValid( const_iterator&iter ) const
{
   return iter != this->end();
}
bool IteratorValid( iterator&iter )
{
   return iter != this->end();
}
iterator FindIndex( int iIndex )
{
   iterator iter  = this->begin();
   int      t     = 0; while( t != iIndex )
   {
      iter++; t++;
   }

   return iter;
}
const_iterator FindIndex( int iIndex ) const
{
   const_iterator iter  = this->begin();
   int            t     = 0; while( t != iIndex )
   {
      iter++; t++;
   }

   return iter;
}
TYPE&GetAt( const iterator&pos )
{
   return *pos;
}
TYPE GetAt( const_iterator&pos ) const
{
   return *pos;
}

};

// simplified and partial only
template<class KEY, class VALUE>
class ZIP_API CZipMap : private std::map<KEY, VALUE>
{
public:
typedef typename std::map<KEY, VALUE>::const_iterator const_iterator;
typedef typename  std::map<KEY, VALUE, std::less<KEY>, std::allocator<std::pair<const KEY, VALUE> > >::value_type v_type;
void SetAt( KEY key, VALUE newValue )
{
    #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
       this->insert( v_type( key, newValue ) );
    #else
       insert( v_type( key, newValue ) );
    #endif
}
BOOL RemoveKey( KEY key )
{
   #if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
   return this->erase( key ) != 0;
   #else	
   return erase( key ) != 0;
   #endif
}
BOOL Lookup( KEY key, VALUE&rValue ) const
{
#if (__GNUC__ == 4 && __GNUC_MINOR__ >= 7 ) || defined( __clang__ )
   const_iterator iter = this->find( key );
#else
   const_iterator iter = find( key );
#endif   

#if ( __GNUC__ >= 3 ) || defined( __clang__ ) // I'm not sure which version precisely should be put here
   if( iter == std::map<KEY, VALUE>::end() )
#else
   if( iter == end() )
#endif
      return FALSE;
   else
   {
      rValue = iter->second;
      return TRUE;
   }
}
};

#if defined( _MSC_VER ) && ( _MSC_VER > 1100 )
        #pragma warning( pop)
#endif

#endif  /* ZIPCOLLECTIONS_DOT_H */

