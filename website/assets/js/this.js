//   /**
//    * Porfolio isotope and filter
//    */
//    window.addEventListener('load', () => {
//     let portfolioContainer = select('.portfolio-container');
//     if (portfolioContainer) {
//       let portfolioIsotope = new Isotope(portfolioContainer, {
//         itemSelector: '.portfolio-item'
//       });

//       let portfolioFilters = select('#portfolio-flters li', true);

//       on('click', '#portfolio-flters li', function(e) {
//         e.preventDefault();
//         portfolioFilters.forEach(function(el) {
//           el.classList.remove('filter-active');
//         });
//         this.classList.add('filter-active');

//         portfolioIsotope.arrange({
//           filter: this.getAttribute('data-filter')
//         });
//         portfolioIsotope.on('arrangeComplete', function() {
//           AOS.refresh()
//         });
//       }, true);
//     }

//   });

//   /**
//    * Initiate portfolio lightbox 
//    */
//   const portfolioLightbox = GLightbox({
//     selector: '.portfolio-lightbox'
//   });


filterSelection("all")
function filterSelection(c) {
  var x, i;
  x = document.getElementsByClassName("filterDiv");
  if (c == "all") c = "";
  for (i = 0; i < x.length; i++) {
    w3RemoveClass(x[i], "show");
    if (x[i].className.indexOf(c) > -1) w3AddClass(x[i], "show");
  }
}

function w3AddClass(element, name) {
  var i, arr1, arr2;
  arr1 = element.className.split(" ");
  arr2 = name.split(" ");
  for (i = 0; i < arr2.length; i++) {
    if (arr1.indexOf(arr2[i]) == -1) {element.className += " " + arr2[i];}
  }
}

function w3RemoveClass(element, name) {
  var i, arr1, arr2;
  arr1 = element.className.split(" ");
  arr2 = name.split(" ");
  for (i = 0; i < arr2.length; i++) {
    while (arr1.indexOf(arr2[i]) > -1) {
      arr1.splice(arr1.indexOf(arr2[i]), 1);     
    }
  }
  element.className = arr1.join(" ");
}

// Add active class to the current button (highlight it)
// var btnContainer = document.getElementById("myBtnContainer");
// var btns = btnContainer.getElementsByClassName("btn");
// for (var i = 0; i < btns.length; i++) {
//   btns[i].addEventListener("click", function(){
//     var current = document.getElementsByClassName("active");
//     current[0].className = current[0].className.replace(" active", "");
//     this.className += " active";
//   });
// }

// Add active class to the current button (highlight it)
// var linkContainer = document.getElementById("mylinkContainer");
// var links = linkContainer.getElementsByClassName("nav-link");
// for (var i = 0; i < links.length; i++) {
//   links[i].addEventListener("click", function(){
//     var current = document.getElementsByClassName("link-active");
//     current[0].className = current[0].className.replace(" link-active", "");
//     this.className += " link-active";
//   });
// }

/**
   * Easy on scroll event listener 
//    */
//  const onscroll = (el, listener) => {
//   el.addEventListener('scroll', listener)
// }

/**
 * Navbar links active state on scroll
 */
// let navbarlinks = select('#navbar .scrollto', true)
// const navbarlinksActive = () => {
//   let position = window.scrollY + 200
//   navbarlinks.forEach(navbarlink => {
//     if (!navbarlink.hash) return
//     let section = select(navbarlink.hash)
//     if (!section) return
//     if (position >= section.offsetTop && position <= (section.offsetTop + section.offsetHeight)) {
//       navbarlink.classList.add('link-active')
//     } else {
//       navbarlink.classList.remove('link-active')
//     }
//   })
// }

// // window.addEventListener('scroll', highlightMenu);
// // window.addEventListener('click', highlightMenu);
// window.addEventListener('click', navbarlinksActive)
// onscroll(document, navbarlinksActive)