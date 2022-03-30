let nixpkgs = import ./nixpkgs.nix;
    pkgs = import nixpkgs {
      overlays = [
        (self: super: {
          tabla = super.callPackage ./derivation.nix {};
        })
      ];
    };
in  pkgs.partitions
