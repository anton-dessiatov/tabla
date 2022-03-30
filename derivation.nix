{ stdenv, lib, cmake, gtest }:

stdenv.mkDerivation {
  name = "tabla";
  src =
    let exclude = path: type:
        let base = baseNameOf path;
            isExcludedDir = type == "directory" && builtins.elem base [ "build" ];
            hasDotPrefix = lib.hasPrefix "." base;
        in  isExcludedDir || hasDotPrefix;
    in  builtins.filterSource (path: type: !exclude path type) ./.;

  nativeBuildInputs = [ cmake ];

  buildInputs = [ gtest ];

  doCheck = true;
}

