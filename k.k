include "object.k";

class ssink
{
  public fun ssink() {
  }

  public fun put( v ) {
    show "default put()";
  }
}

class ssrc
{
  public fun ssrc() {
  }

  public fun get() {
    show "default get()";
    return nil;
  }
}

fun sinkfiller2src( sinkfiller )
{
  var src = new ssrc();
  var get = 11, put = 22;
  var getcont = 33; // void getcont( v ): The cont that came in when get was called
  var putcont = 44; // val putcont(): The cont that came in when put was called

  get = lambda() {
    return callcc lambda( k ) {
      getcont = k;
      putcont();
    };
  };

  put = lambda( v ) {
    callcc lambda( k ) {
      putcont = lambda() {
        k( 1234 );
      };
      getcont( v );
    };
    return;
  };

  src.get = lambda() {
    return get();
  };

  putcont = lambda() {
    var sink = new ssink();
    sink.put = put;
    sinkfiller( sink );
  };

  return src;
}

fun sf1( sink )
{
  for (var i=0; i<10; i=i+1) {
    sink.put( i );
  }
  sink.put( nil );
}

fun double( src ) {
  return lambda( sink ) {
    var done = false;
    while (done==false) {
      var v = src.get();
      sink.put( v );
      sink.put( v );
    }
  };
}

fun dumpsrc( src )
{
  var done = false;
  var count = 0;

  while (done==false) {
    var v = src.get();
    show( "src "+count+" "+v );
    if (v==nil) {
      done = true;
    } else {
      count = count+1;
    }
  }
}

fun srcdumper2sink( srcdumper )
{
  var sink = new ssink();
  var get = 55, put = 66;
  var getcont = 77; // void getcont( v ): The cont that came in when get was called
  var putcont = 88; // val putcont(): The cont that came in when put was called

  get = lambda() {
    return callcc lambda( k ) {
      getcont = k;
      putcont();
    };
  };

  put = lambda( v ) {
    callcc lambda( k ) {
      putcont = lambda() {
        k( 5678 );
      };
//k( 'dum );
      getcont( v );
    };
    return;
  };

  sink.put = lambda( v ) {
    put( v );
  };

  callcc lambda( k ) {
    var src = new ssrc();
    src.get = lambda() {
      return callcc lambda( kk ) {
        getcont = kk;
        src.get = lambda() { return get(); };
        k( 9898 );
      };
    };
    srcdumper( src );
  };

  return sink;
}

var s = sinkfiller2src( sf1 );
dumpsrc( s );
dumpsrc( sinkfiller2src( double( sinkfiller2src( sf1 ) ) ) );

var sq = srcdumper2sink( dumpsrc );
for (var i=0; i<15; i=i+1) {
  sq.put( "a "+i );
}
