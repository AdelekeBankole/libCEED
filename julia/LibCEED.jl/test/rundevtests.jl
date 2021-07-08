using Test, LibCEED, LinearAlgebra, StaticArrays

@testset "LibCEED Development Tests" begin
    @test ceedversion() isa VersionNumber
    @test isrelease() == false
end
