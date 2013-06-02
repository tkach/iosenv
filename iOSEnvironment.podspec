Pod::Spec.new do |s|
  s.name         = "iOSEnvironment"
  s.version      = "0.0.1"
  s.summary      = "iOS environment helpers in one file."

  # s.description  = <<-DESC
  #                   An optional longer description of iOSEnvironment
  #
  #                   * Markdown format.
  #                   * Don't worry about the indent, we strip it!
  #                  DESC

  s.homepage     = "https://github.com/stanislaw/iOSEnvironment"
  s.screenshots  = "https://github.com/stanislaw/iOSEnvironment/iOSEnvironment.png"

  s.license      = { :type => 'MIT', :file => 'LICENSE' }

  s.author       = { "Stanislaw Pankevich" => "s.pankevich@gmail.com" }

  s.source       = { :git => "https://github.com/stanislaw/iOSEnvironment.git", :commit => "71d47c4ca02202e23530d255f1374812a650ffd8" }

  s.platform     = :ios, '5.0'

  s.source_files = 'iOSEnvironment.h'

  s.requires_arc = true
end
