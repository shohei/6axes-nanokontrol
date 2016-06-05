// Generated by CoffeeScript 1.10.0
(function() {
  $(function() {
    var animate, camera, controls, geo, height, light, mat, plane, radians, renderer, scene, width;
    radians = function(degree) {
      return degree * Math.PI / 180;
    };
    width = 500;
    height = 300;
    scene = new THREE.Scene();
    new THREE.JSONLoader().load('cube.json', function(geometry, materials) {
      var geo, mat, mesh;
      geo = geometry;
      mat = new THREE.MeshFaceMaterial(materials);
      mesh = new THREE.Mesh(geo, mat);
      mesh.castShadow = true;
      mesh.scale.set(100, 100, 100);
      return scene.add(mesh);
    });
    geo = new THREE.PlaneGeometry(500, 500);
    mat = new THREE.MeshLambertMaterial({
      color: 0x0096d6,
      side: THREE.DoubleSide
    });
    plane = new THREE.Mesh(geo, mat);
    plane.receiveShadow = true;
    plane.position.set(0, -150, 0);
    plane.rotation.x = radians(90);
    scene.add(plane);
    scene.add(new THREE.AxisHelper(1000));
    light = new THREE.DirectionalLight(0xffffff, 1);
    light.castShadow = true;
    light.position.set(0, 100, 30);
    scene.add(light);
    scene.add(new THREE.AmbientLight(0x550000));
    camera = new THREE.PerspectiveCamera(45, width / height, 1, 1000);
    camera.position.set(200, 300, 500);
    controls = new THREE.TrackballControls(camera);
    renderer = new THREE.WebGLRenderer();
    renderer.shadowMapEnabled = true;
    renderer.setSize(width, height);
    renderer.setClearColor(0xeeeeee, 1);
    $('#stage').append(renderer.domElement);
    animate = function() {
      requestAnimationFrame(animate);
      renderer.render(scene, camera);
      return controls.update();
    };
    return animate();
  });

}).call(this);