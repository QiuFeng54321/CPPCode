/* bezier-spline.js
 *
 * computes cubic bezier coefficients to generate a smooth
 * line through specified points. couples with SVG graphics 
 * for interactive processing.
 *
 * For more info see:
 * http://www.particleincell.com/2012/bezier-splines/ 
 *
 * Lubos Brieda, Particle In Cell Consulting LLC, 2012
 * you may freely use this algorithm in your codes however where feasible
 * please include a link/reference to the source article
 * 
 * correction by Jaco Stuifbergen:
 * in computeControlPoints:
 *	r[n-1] = 3*K[n-1]; // otherwise, the curvature on the last knot is wrong
 * 
 * modification: 
 * the distance of control points is proportional to the distance between knots
I.e. if D(x1,x2) is the distance between x1 and x2,
 and P1[i] , P2[i] are the control points between knots K[i] and K[i+1]
then 
 D(P2[i-1],K[i]) / D(K[i-1],K[i]) = D(K[i],P1[i]) / D(K[i],K[i+1])
 */

var svg = document.documentElement /*svg object*/
var S = new Array() /*splines*/
var V = new Array() /*vertices*/
    // var movingKnot 	/*current object*/
var x0, y0 /*svg offset*/
var colours = ["blue", "red", "green", "brown", "yellow", "magenta"]
var pathIdPrefix = "pathNr_"
var knotIdPrefix = "knotNr_"
var pathWidth = 4
var minWeight = 1 // the calculation of a curve becomes impossible if a distance is 0
var circular = true // the spline will be a loop
var nKnots = -1 // no Knots are defined
var nPaths = circular ? nKnots : nKnots - 1

/*saves elements as global variables*/
function init() {
    /*create control points*/
    var coordString = "{\"x\":[60,220,389,700,600,474,330],\"y\":[60,300,242,240,100,287,390]}"
        //var coordString = "{\"x\":[60,220,220,60],\"y\":[60,60,300,300]}"
        //var coordString = "{\"x\":[60,220,220],\"y\":[60,60,300]}"

    /* create knots and paths */
    stringToKnots(coordString)
}

/* return the coordinates of the knots as a string */
// e.g. {"x":[60,90,220,330],"y":[60,279,300,390]}
function knotsToString() {
    /* encode (x,y) coordinates */
    // JSON.stringify(V) yields an empty array */
    return JSON.stringify(knotCoord())
}

function stringToKnots(text)
/* create knots and paths from a string */
// e.g. {"x":[60,90,220,330],"y":[60,279,300,390]}
{
    var i, coord // x,y coordinates of knots
        /*
        this will
    return a 2 D array */
    coord = JSON.parse(text)

    /* remove old knots, to be sure */
    for (i = 0; i < nKnots; i++) {
        V[i].remove()
    }
    removeAllPaths()

    nKnots = coord.x.length // nPaths = nKnots - 1
    for (i = 0; i < nKnots; i++) {
        V[i] = createKnot(coord.x[i], coord.y[i], i);
    }
    createAllPaths()
        /* calculate the splines */
    updateSplines()
}

function removeAllPaths() {
    var i
    for (i = nPaths - 1; 0 <= i; i--) {
        S[i].remove()
    }
}

function createAllPaths() {
    var i

    nPaths = circular ? nKnots : nKnots - 1
    for (i = 0; i < nPaths; i++) {
        S[i] = createPath(colours[i % colours.length], pathWidth, i);
    }
}
/*creates and adds an SVG circle to represent knots*/
function createKnot(x, y, knotNumber) {
    var Circ = document.createElementNS("http://www.w3.org/2000/svg", "circle")
    Circ.setAttributeNS(null, "id", knotIdPrefix + knotNumber)
    Circ.setAttributeNS(null, "r", 22)
    Circ.setAttributeNS(null, "cx", x)
    Circ.setAttributeNS(null, "cy", y)
    Circ.setAttributeNS(null, "fill", "grey")
    Circ.setAttributeNS(null, "fill-opacity", "0.1")
    Circ.setAttributeNS(null, "stroke", "black")
    Circ.setAttributeNS(null, "stroke-opacity", "1.0")
    Circ.setAttributeNS(null, "stroke-width", "3")
    Circ.setAttributeNS(null, "onmouseover", "evt.target.setAttribute('fill-opacity', '0.5')")
    Circ.setAttributeNS(null, "onmouseout", "evt.target.setAttribute('fill-opacity','0.1');")
    Circ.setAttributeNS(null, "onmousedown", "knotClicked(evt)")
        // Circ.setAttributeNS(null,"onmousedown","removeKnot(evt)")
        // Circ.setAttributeNS(null, "onmouseup","removeKnot(evt);drop(evt)")
    svg.appendChild(Circ)
    return Circ
}

/*creates and adds an SVG path without defining the nodes*/
function createPath(color, width, id) {
    width = (typeof width == 'undefined' ? "4" : width);
    var P = document.createElementNS("http://www.w3.org/2000/svg", "path")
    P.setAttributeNS(null, "id", pathIdPrefix + id)
    P.setAttributeNS(null, "fill", "none")
    P.setAttributeNS(null, "stroke", color)
    P.setAttributeNS(null, "stroke-width", width)
    P.setAttributeNS(null, "onmousedown", "pathClicked(evt)")
    svg.appendChild(P)
    return P
}

/* remove an object */
function remove(id) {
    var parent = event.target.parentNode
    parent.removeChild(id)
}


/*from http://www.w3.org/Graphics/SVG/IG/resources/svgprimer.html*/
function knotClicked(evt) {
    var id = parseInt(evt.target.getAttribute("id").slice(knotIdPrefix.length))
    evt.target.setAttributeNS(null, "fill", "red")
        // evt.target.setAttributeNS(null, "stroke-opacity","0.2")
        // evt.target.setAttributeNS(null, "debugInfo","id is "+id)
    svg.setAttribute("onmouseup", "removeKnot(evt," + id + ")")
    svg.setAttribute("onmouseout", "drop(evt," + id + ")")
}

/*called on mouse move, updates dragged circle and recomputes splines*/
function moveKnot(evenement, id) {
    x = evenement.clientX - x0;
    y = evenement.clientY - y0;

    /*move the current handle*/
    /* applies to circles */
    V[id].setAttributeNS(null, "cx", x)
    V[id].setAttributeNS(null, "cy", y)
        // evt.target.setAttributeNS(null,"cx",x)
        // evt.target.setAttributeNS(null,"cy",y)
        /* test knotsToString and stringToKnots : they work */
        //var temp = knotsToString()
        //document.getElementById("testje").innerHTML = knotsToString()
        // stringToKnots(temp)

    updateSplines();
}

/*called on mouse up, removes circle and updates splines*/
function removeKnot(evenement)
/* applies to circles */
{
    var condemnedKnot = evenement.target
    var id = parseInt(condemnedKnot.getAttribute("id").slice(knotIdPrefix.length))
    condemnedKnot.remove()
    for (i = id; i < nKnots - 1; i++) {
        V[i] = V[i + 1]
        V[i].setAttributeNS(null, "id", knotIdPrefix + (i))
    }

    nKnots--
    nPaths = circular ? nKnots : nKnots - 1
    S[nPaths].remove()
    updateSplines();
}


/*called on mouse move, updates dragged circle and recomputes splines*/
function pathClicked(evt) {
    /*SVG positions are relative to the element but mouse 
      positions are relative to the window, get offset*/
    x0 = getOffset(svg).left;
    y0 = getOffset(svg).top;

    // CurrO=evt.target

    x = evt.clientX - x0;
    y = evt.clientY - y0;

    var id = parseInt(evt.target.getAttribute("id").slice(pathIdPrefix.length))

    insertKnot(id, x, y)

    // create all paths again, so they will be on top of the Knots
    removeAllPaths()
        // we have added a knot, so we must add a path
    nPaths = circular ? nKnots : nKnots - 1
    createAllPaths()
    updateSplines()

    /* set onmousemove */
    svg.setAttribute("onmousemove", "moveKnot(evt," + (id + 1) + ")")

    /* after onmouseup, the knot should not move*/
    svg.setAttribute("onmouseup", "drop(evt," + (id + 1) + ")")
}

function insertKnot(id, x, y) {
    /* distance to the previous and to the next Knot */

    /* inserts a knot between V[id] and V[id+1]
     * (if the distance from (x,y) to those knots is sufficient)*/
    /* pre-condition: 
    V[0] to V[nPaths-1] exist
    id < nPaths
    */

    /* shift array of knots */
    for (i = nKnots; id + 1 < i; i--) {
        V[i] = V[i - 1];
        V[i].setAttributeNS(null, "id", knotIdPrefix + i);
    }
    /* add knot */
    V[id + 1] = createKnot(x, y, id + 1);
    nKnots++
}

function insertPath(id) {
    /* inserts a path between S[id] and S[id+1] if both exist, otherwise after S[id]*/
    /* pre-condition: 
    S[0] to S[nPaths-1] exist
    id < nPaths
    */
    /* shift array of knots */
    /* note: The highest Id for a path is pathIdPrefix+(nPaths-1) */

    for (i = nPaths; id + 1 < i; i--) {
        S[i] = S[i - 1];
        S[i].setAttributeNS(null, "id", pathIdPrefix + i);
    }
    /* add path */
    S[id + 1] = createPath(colours[(id + 1) % colours.length], pathWidth, id + 1);
    nPaths++
}

/*called on mouse up event*/
function drop(evenement, id) {
    // svg  = document.getElementsByTagName('svg')[0];
    svg.setAttributeNS(null, "onmousemove", null)
    svg.setAttributeNS(null, "onmouseup", null)
    svg.setAttributeNS(null, "onmouseout", null)
    V[id].setAttributeNS(null, "fill", "black")
    V[id].setAttributeNS(null, "fill-opacity", "0.1")
    V[id].setAttributeNS(null, "stroke-opacity", "1.0")

}

/*code from http://stackoverflow.com/questions/442404/dynamically-retrieve-html-element-x-y-position-with-javascript*/
function getOffset(el) {
    var _x = 0;
    var _y = 0;
    while (el && !isNaN(el.offsetLeft) && !isNaN(el.offsetTop)) {
        _x += el.offsetLeft - el.scrollLeft;
        _y += el.offsetTop - el.scrollTop;
        el = el.offsetParent;
    }
    return { top: _y, left: _x };
}

/* computes the distance (along a straight line) between the knots */
function distances(x, y) // V is the array of knots
{
    var i, nKnots, result

    nKnots = x.length - 1
    result = new Array(nPaths)
    for (i = 0; i < nKnots; i++) {
        /* calculate Euclidean distance */
        result[i] = Math.sqrt((x[i + 1] - x[i]) ^ 2 + (y[i + 1] - y[i]) ^ 2)
    }

    return result
}

/* return x and y values of knots */
function knotCoord() {
    var i, x, y
    x = new Array(nKnots)
    y = new Array(nKnots)
    for (i = 0; i < nKnots; i++) {
        /*use parseInt to convert string to int*/
        x[i] = parseInt(V[i].getAttributeNS(null, "cx"))
        y[i] = parseInt(V[i].getAttributeNS(null, "cy"))
    }
    return { x: x, y: y };
}

/*computes spline control points*/
function updateSplines() {
    var coord, x, y /* (x,y) coordinates of the knots*/
    var weights // equal to the distances between knots. If knots are nearer, the 3rd derivative can be higher
    var px, py // coordinates of the intermediate control points

    /*grab (x,y) coordinates of the knots */
    coord = knotCoord();
    x = coord.x
    y = coord.y

    //weights = distances (x,y)	
    weights = new Array(nPaths)

    weighting = function(x1, x2, y1, y2) {
        /* calculate Euclidean distance */
        var d = Math.sqrt(Math.pow((x1 - x2), 2) + Math.pow((y1 - y2), 2))
            // if the weight is too small, the calculation becomes instable	
        return d < minWeight ? minWeight : d
    }

    for (i = 0; i < nKnots - 1; i++) {
        weights[i] = weighting(x[i + 1], x[i], y[i + 1], y[i])
    }
    // i = nPaths-1 = nKnots-1
    weights[i] = weighting(x[0], x[i], y[0], y[i])

    /* calculation of the curve */
    /* the equations hold for the P1 control points, they are related to P2 by
     * D(P2[i-1],K[i]) / W[i-1] = D(K[i],P1[i]) / W[i])
     * (where D(M,N) denotes the distance between M and N)
     * W[i] = D(K[i],K[i+1])
     * (so if the distance between nodes is short, the control points will be near)
     */

    px = computeControlPointsCircularW(x, weights);
    py = computeControlPointsCircularW(y, weights);

    /*updates path settings, the browser will draw the new spline*/
    for (i = 0; i < nKnots - 1; i++) {
        S[i].setAttributeNS(null, "d",
            pathDescription(x[i], y[i], px.p1[i], py.p1[i], px.p2[i], py.p2[i], x[i + 1], y[i + 1]));
    }
    if (circular) // for circular loops
    {
        S[i].setAttributeNS(null, "d",
            pathDescription(x[i], y[i], px.p1[i], py.p1[i], px.p2[i], py.p2[i], x[0], y[0]));
    }
}

/*creates formated path string for SVG cubic path element*/
function pathDescription(x1, y1, px1, py1, px2, py2, x2, y2) {
    return "M " + x1 + " " + y1 + " C " + px1 + " " + py1 + " " + px2 + " " + py2 + " " + x2 + " " + y2;
}


function computeControlPointsCircularW(values, weights)
/*computes control points given knots K, this is the brain of the operation*/
/* this version makes the distance of the control points proportional to the distance between the end points.
I.e. if D(x1,x2) is the distance between x1 and x2,
 and P1[i] , P2[i] are the control points between knots K[i] and K[i+1]
then 
 D(P2[i-1],K[i]) / D(K[i-1],K[i]) = D(K[i],P1[i]) / D(K[i],K[i+1])
 
The calculation of the second derivative has been adapted in 2 ways:
If W[i]=D(K[i-1],K[i])/D(K[i+1],K[i]) 
1) 	P2[i-1] = P1[i-1]*W +K[i]*(W[i]+1)
2)	S''[i](0)*W[i]*W[i]=S''[i-1](1)
*/

// required: W has the same length als K 
// calculates the control points (for 1 dimension) of a Béziers curve through the points K, using weights W.
// K should contain all the x-coordinates (or all the y-coordinates)
// K has indices 0..n-1

{
    //document.getElementById("testje").innerHTML = "computeControlPointsCircularW"
    var W = weights.slice() // make a copy of the array
    var K = values.slice()

    var p1, p2, n
    var frac_i

    p2 = new Array();
    n = K.length;

    /*rhs vector*/
    a = new Array();
    b = new Array();
    c = new Array();
    r = new Array();


    /*internal segments*/
    // required: W[n] exists, the same length als K 
    W[-1] = W[n - 1]
    W[n] = W[0]
    K[n] = K[0]
    for (i = 0; i < n; i++) {
        frac_i = W[i] / W[i + 1]
        a[i] = 1 * W[i] * W[i];
        b[i] = 2 * W[i - 1] * (W[i - 1] + W[i]);
        c[i] = W[i - 1] * W[i - 1] * frac_i // W[i]/W[i+1];
        r[i] = Math.pow(W[i - 1] + W[i], 2) * K[i] + Math.pow(W[i - 1], 2) * (1 + frac_i) * K[i + 1];

    }

    /*solves Ax=b with the Thomas algorithm (from Wikipedia)*/
    //p1=parent.Thomas(r,a,b,c)
    /* The previous line provokes the error: (on Chrome, under windows)
    Uncaught SecurityError: Blocked a frame with origin "null" from accessing a frame with origin "null". Protocols, domains, and ports must match.
    In that case, a local function definition would work.
    But I fear that passing data between SVG frames is not possible in such a situation !!!
    */
    // p1=gauss(convertThomasToGauss(r,a,b,c))
    p1 = ThomasCircular_new(r, a, b, c)

    /*we have p1, now compute p2*/
    // required: p1[n] exists
    p1[n] = p1[0]
    for (i = 0; i < n; i++) { //p2[i]=2*K[i+1]-p1[i+1];
        p2[i] = K[i + 1] * (1 + W[i] / W[i + 1]) - p1[i + 1] * (W[i] / W[i + 1]);
    }
    /* alert(" computeControlPointsW i = "+i
    +"\nK = "+K.concat()
    +"\nW = "+W.concat()
    +"\na = "+a.concat()
    +"\nb = "+b.concat()
    +"\nc = "+c.concat()
    +"\nr = "+r.concat()
    +"\np1 = "+p1.concat()
    +"\np2 = "+p2.concat()
    ) */
    return { p1: p1, p2: p2 };
}

function ThomasCircular_new(r_in, a_in, b_in, c_in)
/*solves Ax=r by Guassian elimination (for a matrix that has many zeros)
     r: right-hand vector
    a: array of the sub-diagonal elements (indexes 1 till n-1)
    a[0] is the most up most right element (position [0,n-1])
    b: array of the diagonal elements(indexes 0 till n-1)
    c: array of the upper-diagonal elements(indexed 0 till n-2)
    c[n-1] is the lowest most left element (position [n-1,0])
    all other elements are supposed to be 0
  |   b0 c0 0  0  ...    .      .      .      a0    |
  |   a1 b1 c1 0  ...    .      .      .      0     |
  |   0  a2 b2 c2 ..     .      .      .      0     |
  |   .   . .  .  ...    .      .      .      .     |  x = r
  |   .   . .  .  ...    .      .      .      .     |
  |   0   0 0  0  ... a[n-3] b[n-3] c[n-3]    0     |
  |   0   0 0  0  ...    0   a[n-2] b[n-2]  c[n-2]  |
  |c[n-1] 0 0  0  ...    0      0   a[n-1]  b[n-1]  |
*/
{
    var x, i, n, m
    var r = r_in.slice() // creates a copy
    var a = a_in.slice() // creates a copy
    var b = b_in.slice() // creates a copy
    var c = c_in.slice() // creates a copy
    n = r.length

    // lastcolumn
    // for lc, indexes 0 till n-3 are used. 
    // lc[n-2] is not used, use c[n-2]
    // lc[n-1] is not used, use b[n-1]
    var lc = new Array(n)
    lc[0] = a[0]

    // last row
    // lr contains a value from the last row
    // indexes 0 till n-3 are used. 
    // lr[n-2] is not used, use a[n-1]
    // lr[n-1] is not used, use b[n-1]
    var lr = c[n - 1]

    for (i = 0; i < n - 3; i++) {
        m = a[i + 1] / b[i];
        b[i + 1] -= m * c[i];
        r[i + 1] -= m * r[i];
        // last column // superflous when i=n-2
        lc[i + 1] = -m * lc[i]

        // last row : lr=lr[i]
        m = lr / b[i]
        b[n - 1] -= m * lc[i]
        lr = -m * c[i] // lr=lr[i+1], superflous when i=n-2
            // lr[i]=0 maar deze waarde wordt niet meer gebruikt
        r[n - 1] -= m * r[i]
    }
    // note that i = n-3 now
    {
        m = a[i + 1] / b[i];
        b[i + 1] -= m * c[i];
        r[i + 1] -= m * r[i];
        // last column 
        // in stead of lc[i+1]=-m*lc[i]
        c[i + 1] -= m * lc[i]
            // last row 
        m = lr / b[i]
        b[n - 1] -= m * lc[i]
            // in stead of lr[i+1]= - m * c[i] // superflous when i=n-2
        a[n - 1] -= m * c[i]
            // lr[i]=0 maar deze waarde wordt niet meer gebruikt
        r[n - 1] = r[n - 1] - m * r[i]
    }
    i = n - 2
        // in stead of: for (i = n-1; i < n; i++)
        {
            m = a[i + 1] / b[i];
            // in stead of lr[i+1]= - m * c[i]
            b[i + 1] -= m * c[i];
            // in stead of r[n-1]= r[n-1] - m * r[i] // reeds gedaan
            r[i + 1] -= m * r[i];

            // last column
            // lc[i+1] wordt niet gebruikt, dit is b[i+1]

            // last row
            // lr[i] wordt niet gebruikt, dit is a[i+1]

            // m = lr[i]/b[i];
            // b[i+1] -=  m * c[i] // reeds gedaan
            // lr[i]=0
        }

    x = new Array(n)

    x[n - 1] = r[n - 1] / b[n - 1];
    // the value of lc[n-2] should not be used in the loop
    lc[n - 2] = 0
    for (i = n - 2; i >= 0; --i) {
        x[i] = (r[i] - c[i] * x[i + 1] - lc[i] * x[n - 1]) / b[i];
    }
    return x;
}