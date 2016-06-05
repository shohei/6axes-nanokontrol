$ ->
  radians = (degree) -> degree * Math.PI / 180

  width = 500
  height = 300

  # scene
  scene = new THREE.Scene()

  # mesh
  new THREE.JSONLoader()
    .load 'cube.json', (geometry, materials) ->
              geo = geometry
              mat = new THREE.MeshFaceMaterial materials

              mesh = new THREE.Mesh geo, mat
              mesh.castShadow = true  # shadow
              mesh.scale.set 100, 100, 100
              scene.add mesh

  # mesh (plane)
  geo = new THREE.PlaneGeometry 500, 500
  mat = new THREE.MeshLambertMaterial
                    color : 0x0096d6
                    side : THREE.DoubleSide

  plane = new THREE.Mesh geo, mat
  plane.receiveShadow = true  # shadow
  plane.position.set 0, -150, 0
  plane.rotation.x = radians 90
  scene.add plane

  # axis helper
  scene.add new THREE.AxisHelper 1000

  # light
  light = new THREE.DirectionalLight 0xffffff, 1
  light.castShadow = true # shadow
  light.position.set 0,100,30
  scene.add light

  # ambient light
  scene.add new THREE.AmbientLight 0x550000

  # camera
  camera = new THREE.PerspectiveCamera 45, width / height, 1, 1000
  camera.position.set 200,300,500

  # controls (trackball control)
  controls = new THREE.TrackballControls camera

  # renderer
  renderer = new THREE.WebGLRenderer()
  renderer.shadowMapEnabled = true  # shadow
  renderer.setSize width, height
  renderer.setClearColor 0xeeeeee, 1
  $('#stage').append renderer.domElement

  # rendering
  animate = () ->
    requestAnimationFrame animate
    renderer.render scene, camera
    controls.update()

  animate()

