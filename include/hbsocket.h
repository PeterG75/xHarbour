/*
 * $Id: hbsocket.h 10227 2018-04-11 16:57:04Z lculik $
 */

/*
 * Harbour Project source code:
 *    socket C API
 *
 * Copyright 2009 Przemyslaw Czerpak <druzus / at / priv.onet.pl>
 * www - http://harbour-project.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA (or visit the web site http://www.gnu.org/).
 *
 * As a special exception, the Harbour Project gives permission for
 * additional uses of the text contained in its release of Harbour.
 *
 * The exception is that, if you link the Harbour libraries with other
 * files to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the Harbour library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * This exception applies only to the code released by the Harbour
 * Project under the name Harbour.  If you copy code from other
 * Harbour Project or Free Software Foundation releases into a copy of
 * Harbour, as the General Public License permits, the exception does
 * not apply to the code that you add in this way.  To avoid misleading
 * anyone as to the status of such modified files, you must delete
 * this exception notice from them.
 *
 * If you write modifications of your own for Harbour, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.
 *
 */

#ifndef HB_SOCKET_H_
#define HB_SOCKET_H_

#include "hbapi.h"
#include "hbsocket.ch"

HB_EXTERN_BEGIN

#if defined( HB_OS_WIN ) && ! defined( HB_OS_UNIX )
   typedef HB_PTRUINT   HB_SOCKET;
#else
   typedef int          HB_SOCKET;
#endif

typedef HB_SOCKET ( * HB_SOCKET_FUNC )( PHB_ITEM );

#define HB_NO_SOCKET          ( ( HB_SOCKET ) -1 )

extern HB_EXPORT void         hb_socketAutoInit( void );
extern HB_EXPORT int          hb_socketInit( void );
extern HB_EXPORT void         hb_socketCleanup( void );
extern HB_EXPORT int          hb_socketGetError( void );
extern HB_EXPORT int          hb_socketGetOsError( void );
extern HB_EXPORT const char * hb_socketErrorStr( int iError );
extern HB_EXPORT void         hb_socketSetError( int iError );
extern HB_EXPORT int          hb_socketGetAddrFamily( const void * pSockAddr, unsigned len );
extern HB_EXPORT BOOL         hb_socketLocalAddr( void ** pSockAddr, unsigned * puiLen, const char * szAddr );
extern HB_EXPORT BOOL         hb_socketInetAddr( void ** pSockAddr, unsigned * puiLen, const char * szAddr, int iPort );
extern HB_EXPORT BOOL         hb_socketInet6Addr( void ** pSockAddr, unsigned * puiLen, const char * szAddr, int iPort );
extern HB_EXPORT char *       hb_socketAddrGetName( const void * pSockAddr, unsigned len );
extern HB_EXPORT BOOL         hb_socketResolveInetAddr( void ** pSockAddr, unsigned * puiLen, const char * szAddr, int iPort );
extern HB_EXPORT char *       hb_socketResolveAddr( const char * szAddr, int af );
extern HB_EXPORT PHB_ITEM     hb_socketGetHosts( const char * szAddr, int af );
extern HB_EXPORT PHB_ITEM     hb_socketGetAliases( const char * szAddr, int af );
extern HB_EXPORT char *       hb_socketGetHostName( const void * pSockAddr, unsigned len );
extern HB_EXPORT PHB_ITEM     hb_socketGetIFaces( int af, BOOL fNoAliases );
extern HB_EXPORT int          hb_socketAddrGetPort( const void * pSockAddr, unsigned len );
extern HB_EXPORT BOOL         hb_socketAddrFromItem( void ** pSockAddr, unsigned * puiLen, PHB_ITEM pAddrItm );
extern HB_EXPORT PHB_ITEM     hb_socketAddrToItem( const void * pSockAddr, unsigned len );
extern HB_EXPORT int          hb_socketGetSockName( HB_SOCKET sd, void ** pSockAddr, unsigned * puiLen );
extern HB_EXPORT int          hb_socketGetPeerName( HB_SOCKET sd, void ** pSockAddr, unsigned * puiLen );
extern HB_EXPORT HB_SOCKET    hb_socketOpen( int domain, int type, int protocol );
extern HB_EXPORT int          hb_socketClose( HB_SOCKET sd );
extern HB_EXPORT int          hb_socketShutdown( HB_SOCKET sd, int iMode );
extern HB_EXPORT int          hb_socketBind( HB_SOCKET sd, const void * pSockAddr, unsigned uiLen );
extern HB_EXPORT int          hb_socketListen( HB_SOCKET sd, int iBacklog );
extern HB_EXPORT HB_SOCKET    hb_socketAccept( HB_SOCKET sd, void ** pSockAddr, unsigned * puiLen, HB_LONG timeout );
extern HB_EXPORT int          hb_socketConnect( HB_SOCKET sd, const void * pSockAddr, unsigned uiLen, HB_LONG timeout );
extern HB_EXPORT long         hb_socketSend( HB_SOCKET sd, const void * data, long len, int flags, HB_LONG timeout );
extern HB_EXPORT long         hb_socketSendTo( HB_SOCKET sd, const void * data, long len, int flags, const void * pSockAddr, unsigned uiSockLen, HB_LONG timeout );
extern HB_EXPORT long         hb_socketRecv( HB_SOCKET sd, void * data, long len, int flags, HB_LONG timeout );
extern HB_EXPORT long         hb_socketRecvFrom( HB_SOCKET sd, void * data, long len, int flags, void ** pSockAddr, unsigned * puiSockLen, HB_LONG timeout );
extern HB_EXPORT int          hb_socketSetBlockingIO( HB_SOCKET sd, BOOL fBlocking );
extern HB_EXPORT int          hb_socketSetNoDelay( HB_SOCKET sd, BOOL fNoDelay );
extern HB_EXPORT int          hb_socketSetExclusiveAddr( HB_SOCKET sd, BOOL fExclusive );
extern HB_EXPORT int          hb_socketSetReuseAddr( HB_SOCKET sd, BOOL fReuse );
extern HB_EXPORT int          hb_socketSetKeepAlive( HB_SOCKET sd, BOOL fKeepAlive );
extern HB_EXPORT int          hb_socketSetBroadcast( HB_SOCKET sd, BOOL fBroadcast );
extern HB_EXPORT int          hb_socketSetSndBufSize( HB_SOCKET sd, int iSize );
extern HB_EXPORT int          hb_socketSetRcvBufSize( HB_SOCKET sd, int iSize );
extern HB_EXPORT int          hb_socketGetRcvBufSize( HB_SOCKET sd, int * piSize );
extern HB_EXPORT int          hb_socketGetSndBufSize( HB_SOCKET sd, int * piSize );
extern HB_EXPORT int          hb_socketSetMulticast( HB_SOCKET sd, int af, const char * szAddr );
extern HB_EXPORT int          hb_socketSelectRead( HB_SOCKET sd, HB_LONG timeout );
extern HB_EXPORT int          hb_socketSelectWrite( HB_SOCKET sd, HB_LONG timeout );
extern HB_EXPORT int          hb_socketSelectWriteEx( HB_SOCKET sd, HB_LONG timeout );
extern HB_EXPORT int          hb_socketSelect( PHB_ITEM pArrayRD, BOOL fSetRD,
                                               PHB_ITEM pArrayWR, BOOL fSetWR,
                                               PHB_ITEM pArrayEX, BOOL fSetEX,
                                               HB_LONG timeout, HB_SOCKET_FUNC pFunc );

/* Harbour level socket item API functions */
extern HB_EXPORT HB_SOCKET hb_socketParam( int iParam );
extern HB_EXPORT HB_SOCKET hb_socketItemGet( PHB_ITEM pItem );
extern HB_EXPORT PHB_ITEM  hb_socketItemPut( PHB_ITEM pItem, HB_SOCKET sd );
extern HB_EXPORT void      hb_socketItemClear( PHB_ITEM pItem );

#define HB_SOCKET_FILTER_MAX  128

struct _HB_SOCKEX;
typedef struct _HB_SOCKEX * PHB_SOCKEX;

#if defined( _HB_SOCKEX_IMPLEMENTATION_ )

typedef struct
{
   const char * pszName;
   PHB_SOCKEX  ( * New )      ( HB_SOCKET sd, PHB_ITEM pParams );
   PHB_SOCKEX  ( * Next )     ( PHB_SOCKEX pSock, PHB_ITEM pParams );
   int         ( * Close )    ( PHB_SOCKEX pSock, BOOL fClose );
   long        ( * Read )     ( PHB_SOCKEX pSock, void * data, long len, HB_LONG timeout );
   long        ( * Write )    ( PHB_SOCKEX pSock, const void * data, long len, HB_LONG timeout );
   long        ( * Flush )    ( PHB_SOCKEX pSock, HB_LONG timeout, BOOL fSync );
   int         ( * CanRead )  ( PHB_SOCKEX pSock, BOOL fBuffer, HB_LONG timeout );
   int         ( * CanWrite ) ( PHB_SOCKEX pSock, BOOL fBuffer, HB_LONG timeout );
   char *      ( * Name )     ( PHB_SOCKEX pSock );
   const char *( * ErrorStr ) ( PHB_SOCKEX pSock, int iError );
}
HB_SOCKET_FILTER, * PHB_SOCKET_FILTER;

typedef struct _HB_SOCKEX
{
   HB_SOCKET sd;
   BOOL   fRedirAll;
   BOOL   fShutDown;
   int       iAutoFlush;
   long      inbuffer;
   long      posbuffer;
   long      readahead;
   HB_BYTE * buffer;
   void *    cargo;
   const HB_SOCKET_FILTER * pFilter;
}
HB_SOCKEX;

extern HB_EXPORT int  hb_sockexRegister( const HB_SOCKET_FILTER * pFilter );

#endif /* _HB_SOCKEX_IMPLEMENTATION_ */

extern HB_EXPORT int  hb_sockexClose( PHB_SOCKEX pSock, BOOL fClose );
extern HB_EXPORT long hb_sockexRead ( PHB_SOCKEX pSock, void * data, long len, HB_LONG timeout );
extern HB_EXPORT long hb_sockexWrite( PHB_SOCKEX pSock, const void * data, long len, HB_LONG timeout );
extern HB_EXPORT long hb_sockexFlush( PHB_SOCKEX pSock, HB_LONG timeout, BOOL fSync );

extern HB_EXPORT int  hb_sockexCanRead ( PHB_SOCKEX pSock, BOOL fBuffer, HB_LONG timeout );
extern HB_EXPORT int  hb_sockexCanWrite( PHB_SOCKEX pSock, BOOL fBuffer, HB_LONG timeout );
extern HB_EXPORT int  hb_sockexSelect( PHB_ITEM pArrayRD, BOOL fSetRD,
                                       PHB_ITEM pArrayWR, BOOL fSetWR,
                                       PHB_ITEM pArrayEX, BOOL fSetEX,
                                       HB_LONG timeout, HB_SOCKET_FUNC pFunc );

extern HB_EXPORT BOOL    hb_sockexIsRaw( PHB_SOCKEX pSock );
extern HB_EXPORT int        hb_sockexRawClear( PHB_SOCKEX pSock, BOOL fClear );
extern HB_EXPORT HB_SOCKET  hb_sockexGetHandle( PHB_SOCKEX pSock );
extern HB_EXPORT void       hb_sockexClearHandle( PHB_SOCKEX pSock );
extern HB_EXPORT void       hb_sockexSetShutDown( PHB_SOCKEX pSock, BOOL fShutDown );
extern HB_EXPORT BOOL    hb_sockexGetShutDown( PHB_SOCKEX pSock );
extern HB_EXPORT void       hb_sockexSetAutoFlush( PHB_SOCKEX pSock, int iAutoFlush );
extern HB_EXPORT int        hb_sockexGetAutoFlush( PHB_SOCKEX pSock );

extern HB_EXPORT void       hb_socekxParamsInit( PHB_SOCKEX pSock, PHB_ITEM pParams );
extern HB_EXPORT void       hb_socekxParamsGetStd( PHB_ITEM pParams,
                                                   const void ** pKeydata, int * pKeylen,
                                                   const void ** pIV, int * pIVlen,
                                                   int * pLevel, int * pStrategy );
extern HB_EXPORT PHB_SOCKEX hb_sockexNew( HB_SOCKET sd, const char * pszFilter, PHB_ITEM pParams );
extern HB_EXPORT PHB_SOCKEX hb_sockexNext( PHB_SOCKEX pSock, const char * pszFilter, PHB_ITEM pParams );
extern HB_EXPORT char *     hb_sockexName( PHB_SOCKEX pSock );
extern HB_EXPORT const char * hb_sockexErrorStr( PHB_SOCKEX pSock, int iError );
extern HB_EXPORT PHB_SOCKEX hb_sockexParam( int iParam );
extern HB_EXPORT PHB_SOCKEX hb_sockexItemGet( PHB_ITEM pItem );
extern HB_EXPORT PHB_ITEM   hb_sockexItemPut( PHB_ITEM pItem, PHB_SOCKEX pSock );
extern HB_EXPORT void       hb_sockexItemClear( PHB_ITEM pItem );
extern HB_EXPORT BOOL    hb_sockexItemReplace( PHB_ITEM pItem, PHB_SOCKEX pSock );
extern HB_EXPORT BOOL    hb_sockexItemSetFilter( PHB_ITEM pItem, const char * pszFilter, PHB_ITEM pParams );

HB_EXTERN_END

#endif /* HB_SOCKET_H_ */
