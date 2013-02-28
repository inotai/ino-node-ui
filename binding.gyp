{
  'targets': [
    {
      'target_name': 'ui',
      'sources': [
        'src/module-idlers.cpp',
      ],
      'include_dirs': [
        'src',
      ],
      'defines': [
        'WIN32',
        '_WIN32',
        '_WINDOWS',
        '_UNICODE=1'
      ],
      'msvs_configuration_attributes': {
        'CharacterSet': '1',
      }
    }
  ]
}