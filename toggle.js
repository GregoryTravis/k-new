// $Id: toggle.js,v 1.1 2004/08/06 14:14:30 greg Exp $

function toggleChildren( parent, e )
{
  if (!e) {
    alert( "Can't get event" );
  }
  if (!document.getElementById) {
    alert( "!document.getElementById" );
  }
  var div = document.getElementById( parent+"c" );

  if (div.style.display == 'none') {
    div.style.display = 'block';
  } else if (div.style.display == 'block') {
    div.style.display = 'none';
  } else {
    alert( div.style.display+"??" );
  }

  var pm = document.getElementById( parent+"pm" );
  if (pm) {
    if (div.style.display == 'none') {
      pm.innerHTML = "+";
    } else if (div.style.display == 'block') {
      pm.innerHTML = "-";
    }
  }

  if (e) {
    e.cancelBubble = true;
    if (e.stopPropagation) {
      e.stopPropagation();
    }
  }
}
