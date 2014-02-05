MRuby::Build.new do |conf|
  # load specific toolchain settings

  if ENV['VisualStudioVersion']
    toolchain :visualcpp
  else
    toolchain :gcc
  end

  conf.gembox 'default'

end

MRuby::CrossBuild.new(:blackberry) do |conf|
  toolchain :gcc

  QNX = "/Applications/Momentics.app"
  QNX_HOST = "#{QNX}/host_10_2_0_15"
  QNX_BINS = "#{QNX_HOST}/darwin/x86/usr/bin"
  QNX_TARGET = "#{QNX}/target_10_2_0_1155/qnx6"
  QNX_INCLUDES = "#{QNX}/target_10_2_0_1155/qnx6/usr/include"
  QNX_LYBRARY = "#{QNX}/target_10_2_0_1155/qnx6/armle-v7/usr/lib"


  conf.cc.command = "#{QNX_BINS}/qcc"
  conf.cc.flags = %w{-Vgcc_ntoarmv7le}
  conf.cc.include_paths = [QNX_INCLUDES, "#{MRUBY_ROOT}/include"]

  conf.cxx.command = "#{QNX_BINS}/qcc"
  conf.cxx.flags = %w{-Vgcc_ntoarmv7le}
  conf.cxx.include_paths = [QNX_INCLUDES, "#{MRUBY_ROOT}/include"]

  conf.linker.command = "#{QNX_BINS}/qcc"
  conf.linker.flags = %w{-Vgcc_ntoarmv7le}
  conf.linker.library_paths = [QNX_LYBRARY]

  conf.archiver do |archiver|
    archiver.command = "#{QNX_BINS}/ntoarmv7-ar"
    #archiver.archive_options = 'rcs %{outfile} %{objs}'
  end

  conf.yacc.command = "#{QNX_BINS}/bison"

  #do not build test executable
  #conf.build_mrbtest_lib_only

  conf.gembox 'full-core'
end
