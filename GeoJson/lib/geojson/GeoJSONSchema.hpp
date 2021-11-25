#ifndef GEO_JSON_SCHEMA_HPP
#define GEO_JSON_SCHEMA_HPP

constexpr char GeoJsonSchema[] { R"json(
{
  "$schema": "http://json-schema.org/draft-04/schema#",
  "$id": "https://geojson.org/schema/GeoJSON.json",
  "title": "GeoJSON",
  "oneOf": [
    {
      "title": "GeoJSON Point",
      "type": "object",
      "required": [
        "type",
        "coordinates"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "Point"
          ]
        },
        "coordinates": {
          "type": "array",
          "minItems": 2,
          "items": {
            "type": "string"
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON LineString",
      "type": "object",
      "required": [
        "type",
        "coordinates"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "LineString"
          ]
        },
        "coordinates": {
          "type": "array",
          "minItems": 2,
          "items": {
            "type": "array",
            "minItems": 2,
            "items": {
              "type": "string"
            }
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON Polygon",
      "type": "object",
      "required": [
        "type",
        "coordinates"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "Polygon"
          ]
        },
        "coordinates": {
          "type": "array",
          "items": {
            "type": "array",
            "minItems": 4,
            "items": {
              "type": "array",
              "minItems": 2,
              "items": {
                "type": "string"
              }
            }
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON MultiPoint",
      "type": "object",
      "required": [
        "type",
        "coordinates"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "MultiPoint"
          ]
        },
        "coordinates": {
          "type": "array",
          "items": {
            "type": "array",
            "minItems": 2,
            "items": {
              "type": "string"
            }
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON MultiLineString",
      "type": "object",
      "required": [
        "type",
        "coordinates"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "MultiLineString"
          ]
        },
        "coordinates": {
          "type": "array",
          "items": {
            "type": "array",
            "minItems": 2,
            "items": {
              "type": "array",
              "minItems": 2,
              "items": {
                "type": "string"
              }
            }
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON MultiPolygon",
      "type": "object",
      "required": [
        "type",
        "coordinates"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "MultiPolygon"
          ]
        },
        "coordinates": {
          "type": "array",
          "items": {
            "type": "array",
            "items": {
              "type": "array",
              "minItems": 4,
              "items": {
                "type": "array",
                "minItems": 2,
                "items": {
                  "type": "string"
                }
              }
            }
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON GeometryCollection",
      "type": "object",
      "required": [
        "type",
        "geometries"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "GeometryCollection"
          ]
        },
        "geometries": {
          "type": "array",
          "items": {
            "oneOf": [
              {
                "title": "GeoJSON Point",
                "type": "object",
                "required": [
                  "type",
                  "coordinates"
                ],
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": [
                      "Point"
                    ]
                  },
                  "coordinates": {
                    "type": "array",
                    "minItems": 2,
                    "items": {
                      "type": "string"
                    }
                  },
                  "bbox": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "string"
                    }
                  }
                }
              },
              {
                "title": "GeoJSON LineString",
                "type": "object",
                "required": [
                  "type",
                  "coordinates"
                ],
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": [
                      "LineString"
                    ]
                  },
                  "coordinates": {
                    "type": "array",
                    "minItems": 2,
                    "items": {
                      "type": "array",
                      "minItems": 2,
                      "items": {
                        "type": "string"
                      }
                    }
                  },
                  "bbox": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "string"
                    }
                  }
                }
              },
              {
                "title": "GeoJSON Polygon",
                "type": "object",
                "required": [
                  "type",
                  "coordinates"
                ],
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": [
                      "Polygon"
                    ]
                  },
                  "coordinates": {
                    "type": "array",
                    "items": {
                      "type": "array",
                      "minItems": 4,
                      "items": {
                        "type": "array",
                        "minItems": 2,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  "bbox": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "string"
                    }
                  }
                }
              },
              {
                "title": "GeoJSON MultiPoint",
                "type": "object",
                "required": [
                  "type",
                  "coordinates"
                ],
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": [
                      "MultiPoint"
                    ]
                  },
                  "coordinates": {
                    "type": "array",
                    "items": {
                      "type": "array",
                      "minItems": 2,
                      "items": {
                        "type": "string"
                      }
                    }
                  },
                  "bbox": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "string"
                    }
                  }
                }
              },
              {
                "title": "GeoJSON MultiLineString",
                "type": "object",
                "required": [
                  "type",
                  "coordinates"
                ],
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": [
                      "MultiLineString"
                    ]
                  },
                  "coordinates": {
                    "type": "array",
                    "items": {
                      "type": "array",
                      "minItems": 2,
                      "items": {
                        "type": "array",
                        "minItems": 2,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  "bbox": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "string"
                    }
                  }
                }
              },
              {
                "title": "GeoJSON MultiPolygon",
                "type": "object",
                "required": [
                  "type",
                  "coordinates"
                ],
                "properties": {
                  "type": {
                    "type": "string",
                    "enum": [
                      "MultiPolygon"
                    ]
                  },
                  "coordinates": {
                    "type": "array",
                    "items": {
                      "type": "array",
                      "items": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "array",
                          "minItems": 2,
                          "items": {
                            "type": "string"
                          }
                        }
                      }
                    }
                  },
                  "bbox": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "string"
                    }
                  }
                }
              }
            ]
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON Feature",
      "type": "object",
      "required": [
        "type",
        "properties",
        "geometry"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "Feature"
          ]
        },
        "id": {
          "oneOf": [
            {
              "type": "string"
            },
            {
              "type": "string"
            }
          ]
        },
        "properties": {
          "oneOf": [
            {
              "type": "null"
            },
            {
              "type": "object"
            }
          ]
        },
        "geometry": {
          "oneOf": [
            {
              "type": "null"
            },
            {
              "title": "GeoJSON Point",
              "type": "object",
              "required": [
                "type",
                "coordinates"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "Point"
                  ]
                },
                "coordinates": {
                  "type": "array",
                  "minItems": 2,
                  "items": {
                    "type": "string"
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            },
            {
              "title": "GeoJSON LineString",
              "type": "object",
              "required": [
                "type",
                "coordinates"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "LineString"
                  ]
                },
                "coordinates": {
                  "type": "array",
                  "minItems": 2,
                  "items": {
                    "type": "array",
                    "minItems": 2,
                    "items": {
                      "type": "string"
                    }
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            },
            {
              "title": "GeoJSON Polygon",
              "type": "object",
              "required": [
                "type",
                "coordinates"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "Polygon"
                  ]
                },
                "coordinates": {
                  "type": "array",
                  "items": {
                    "type": "array",
                    "minItems": 4,
                    "items": {
                      "type": "array",
                      "minItems": 2,
                      "items": {
                        "type": "string"
                      }
                    }
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            },
            {
              "title": "GeoJSON MultiPoint",
              "type": "object",
              "required": [
                "type",
                "coordinates"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "MultiPoint"
                  ]
                },
                "coordinates": {
                  "type": "array",
                  "items": {
                    "type": "array",
                    "minItems": 2,
                    "items": {
                      "type": "string"
                    }
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            },
            {
              "title": "GeoJSON MultiLineString",
              "type": "object",
              "required": [
                "type",
                "coordinates"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "MultiLineString"
                  ]
                },
                "coordinates": {
                  "type": "array",
                  "items": {
                    "type": "array",
                    "minItems": 2,
                    "items": {
                      "type": "array",
                      "minItems": 2,
                      "items": {
                        "type": "string"
                      }
                    }
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            },
            {
              "title": "GeoJSON MultiPolygon",
              "type": "object",
              "required": [
                "type",
                "coordinates"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "MultiPolygon"
                  ]
                },
                "coordinates": {
                  "type": "array",
                  "items": {
                    "type": "array",
                    "items": {
                      "type": "array",
                      "minItems": 4,
                      "items": {
                        "type": "array",
                        "minItems": 2,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            },
            {
              "title": "GeoJSON GeometryCollection",
              "type": "object",
              "required": [
                "type",
                "geometries"
              ],
              "properties": {
                "type": {
                  "type": "string",
                  "enum": [
                    "GeometryCollection"
                  ]
                },
                "geometries": {
                  "type": "array",
                  "items": {
                    "oneOf": [
                      {
                        "title": "GeoJSON Point",
                        "type": "object",
                        "required": [
                          "type",
                          "coordinates"
                        ],
                        "properties": {
                          "type": {
                            "type": "string",
                            "enum": [
                              "Point"
                            ]
                          },
                          "coordinates": {
                            "type": "array",
                            "minItems": 2,
                            "items": {
                              "type": "string"
                            }
                          },
                          "bbox": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      {
                        "title": "GeoJSON LineString",
                        "type": "object",
                        "required": [
                          "type",
                          "coordinates"
                        ],
                        "properties": {
                          "type": {
                            "type": "string",
                            "enum": [
                              "LineString"
                            ]
                          },
                          "coordinates": {
                            "type": "array",
                            "minItems": 2,
                            "items": {
                              "type": "array",
                              "minItems": 2,
                              "items": {
                                "type": "string"
                              }
                            }
                          },
                          "bbox": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      {
                        "title": "GeoJSON Polygon",
                        "type": "object",
                        "required": [
                          "type",
                          "coordinates"
                        ],
                        "properties": {
                          "type": {
                            "type": "string",
                            "enum": [
                              "Polygon"
                            ]
                          },
                          "coordinates": {
                            "type": "array",
                            "items": {
                              "type": "array",
                              "minItems": 4,
                              "items": {
                                "type": "array",
                                "minItems": 2,
                                "items": {
                                  "type": "string"
                                }
                              }
                            }
                          },
                          "bbox": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      {
                        "title": "GeoJSON MultiPoint",
                        "type": "object",
                        "required": [
                          "type",
                          "coordinates"
                        ],
                        "properties": {
                          "type": {
                            "type": "string",
                            "enum": [
                              "MultiPoint"
                            ]
                          },
                          "coordinates": {
                            "type": "array",
                            "items": {
                              "type": "array",
                              "minItems": 2,
                              "items": {
                                "type": "string"
                              }
                            }
                          },
                          "bbox": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      {
                        "title": "GeoJSON MultiLineString",
                        "type": "object",
                        "required": [
                          "type",
                          "coordinates"
                        ],
                        "properties": {
                          "type": {
                            "type": "string",
                            "enum": [
                              "MultiLineString"
                            ]
                          },
                          "coordinates": {
                            "type": "array",
                            "items": {
                              "type": "array",
                              "minItems": 2,
                              "items": {
                                "type": "array",
                                "minItems": 2,
                                "items": {
                                  "type": "string"
                                }
                              }
                            }
                          },
                          "bbox": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      {
                        "title": "GeoJSON MultiPolygon",
                        "type": "object",
                        "required": [
                          "type",
                          "coordinates"
                        ],
                        "properties": {
                          "type": {
                            "type": "string",
                            "enum": [
                              "MultiPolygon"
                            ]
                          },
                          "coordinates": {
                            "type": "array",
                            "items": {
                              "type": "array",
                              "items": {
                                "type": "array",
                                "minItems": 4,
                                "items": {
                                  "type": "array",
                                  "minItems": 2,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            }
                          },
                          "bbox": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      }
                    ]
                  }
                },
                "bbox": {
                  "type": "array",
                  "minItems": 4,
                  "items": {
                    "type": "string"
                  }
                }
              }
            }
          ]
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    },
    {
      "title": "GeoJSON FeatureCollection",
      "type": "object",
      "required": [
        "type",
        "features"
      ],
      "properties": {
        "type": {
          "type": "string",
          "enum": [
            "FeatureCollection"
          ]
        },
        "features": {
          "type": "array",
          "items": {
            "title": "GeoJSON Feature",
            "type": "object",
            "required": [
              "type",
              "properties",
              "geometry"
            ],
            "properties": {
              "type": {
                "type": "string",
                "enum": [
                  "Feature"
                ]
              },
              "id": {
                "oneOf": [
                  {
                    "type": "string"
                  },
                  {
                    "type": "string"
                  }
                ]
              },
              "properties": {
                "oneOf": [
                  {
                    "type": "null"
                  },
                  {
                    "type": "object"
                  }
                ]
              },
              "geometry": {
                "oneOf": [
                  {
                    "type": "null"
                  },
                  {
                    "title": "GeoJSON Point",
                    "type": "object",
                    "required": [
                      "type",
                      "coordinates"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "Point"
                        ]
                      },
                      "coordinates": {
                        "type": "array",
                        "minItems": 2,
                        "items": {
                          "type": "string"
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  {
                    "title": "GeoJSON LineString",
                    "type": "object",
                    "required": [
                      "type",
                      "coordinates"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "LineString"
                        ]
                      },
                      "coordinates": {
                        "type": "array",
                        "minItems": 2,
                        "items": {
                          "type": "array",
                          "minItems": 2,
                          "items": {
                            "type": "string"
                          }
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  {
                    "title": "GeoJSON Polygon",
                    "type": "object",
                    "required": [
                      "type",
                      "coordinates"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "Polygon"
                        ]
                      },
                      "coordinates": {
                        "type": "array",
                        "items": {
                          "type": "array",
                          "minItems": 4,
                          "items": {
                            "type": "array",
                            "minItems": 2,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  {
                    "title": "GeoJSON MultiPoint",
                    "type": "object",
                    "required": [
                      "type",
                      "coordinates"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "MultiPoint"
                        ]
                      },
                      "coordinates": {
                        "type": "array",
                        "items": {
                          "type": "array",
                          "minItems": 2,
                          "items": {
                            "type": "string"
                          }
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  {
                    "title": "GeoJSON MultiLineString",
                    "type": "object",
                    "required": [
                      "type",
                      "coordinates"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "MultiLineString"
                        ]
                      },
                      "coordinates": {
                        "type": "array",
                        "items": {
                          "type": "array",
                          "minItems": 2,
                          "items": {
                            "type": "array",
                            "minItems": 2,
                            "items": {
                              "type": "string"
                            }
                          }
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  {
                    "title": "GeoJSON MultiPolygon",
                    "type": "object",
                    "required": [
                      "type",
                      "coordinates"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "MultiPolygon"
                        ]
                      },
                      "coordinates": {
                        "type": "array",
                        "items": {
                          "type": "array",
                          "items": {
                            "type": "array",
                            "minItems": 4,
                            "items": {
                              "type": "array",
                              "minItems": 2,
                              "items": {
                                "type": "string"
                              }
                            }
                          }
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  },
                  {
                    "title": "GeoJSON GeometryCollection",
                    "type": "object",
                    "required": [
                      "type",
                      "geometries"
                    ],
                    "properties": {
                      "type": {
                        "type": "string",
                        "enum": [
                          "GeometryCollection"
                        ]
                      },
                      "geometries": {
                        "type": "array",
                        "items": {
                          "oneOf": [
                            {
                              "title": "GeoJSON Point",
                              "type": "object",
                              "required": [
                                "type",
                                "coordinates"
                              ],
                              "properties": {
                                "type": {
                                  "type": "string",
                                  "enum": [
                                    "Point"
                                  ]
                                },
                                "coordinates": {
                                  "type": "array",
                                  "minItems": 2,
                                  "items": {
                                    "type": "string"
                                  }
                                },
                                "bbox": {
                                  "type": "array",
                                  "minItems": 4,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            },
                            {
                              "title": "GeoJSON LineString",
                              "type": "object",
                              "required": [
                                "type",
                                "coordinates"
                              ],
                              "properties": {
                                "type": {
                                  "type": "string",
                                  "enum": [
                                    "LineString"
                                  ]
                                },
                                "coordinates": {
                                  "type": "array",
                                  "minItems": 2,
                                  "items": {
                                    "type": "array",
                                    "minItems": 2,
                                    "items": {
                                      "type": "string"
                                    }
                                  }
                                },
                                "bbox": {
                                  "type": "array",
                                  "minItems": 4,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            },
                            {
                              "title": "GeoJSON Polygon",
                              "type": "object",
                              "required": [
                                "type",
                                "coordinates"
                              ],
                              "properties": {
                                "type": {
                                  "type": "string",
                                  "enum": [
                                    "Polygon"
                                  ]
                                },
                                "coordinates": {
                                  "type": "array",
                                  "items": {
                                    "type": "array",
                                    "minItems": 4,
                                    "items": {
                                      "type": "array",
                                      "minItems": 2,
                                      "items": {
                                        "type": "string"
                                      }
                                    }
                                  }
                                },
                                "bbox": {
                                  "type": "array",
                                  "minItems": 4,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            },
                            {
                              "title": "GeoJSON MultiPoint",
                              "type": "object",
                              "required": [
                                "type",
                                "coordinates"
                              ],
                              "properties": {
                                "type": {
                                  "type": "string",
                                  "enum": [
                                    "MultiPoint"
                                  ]
                                },
                                "coordinates": {
                                  "type": "array",
                                  "items": {
                                    "type": "array",
                                    "minItems": 2,
                                    "items": {
                                      "type": "string"
                                    }
                                  }
                                },
                                "bbox": {
                                  "type": "array",
                                  "minItems": 4,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            },
                            {
                              "title": "GeoJSON MultiLineString",
                              "type": "object",
                              "required": [
                                "type",
                                "coordinates"
                              ],
                              "properties": {
                                "type": {
                                  "type": "string",
                                  "enum": [
                                    "MultiLineString"
                                  ]
                                },
                                "coordinates": {
                                  "type": "array",
                                  "items": {
                                    "type": "array",
                                    "minItems": 2,
                                    "items": {
                                      "type": "array",
                                      "minItems": 2,
                                      "items": {
                                        "type": "string"
                                      }
                                    }
                                  }
                                },
                                "bbox": {
                                  "type": "array",
                                  "minItems": 4,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            },
                            {
                              "title": "GeoJSON MultiPolygon",
                              "type": "object",
                              "required": [
                                "type",
                                "coordinates"
                              ],
                              "properties": {
                                "type": {
                                  "type": "string",
                                  "enum": [
                                    "MultiPolygon"
                                  ]
                                },
                                "coordinates": {
                                  "type": "array",
                                  "items": {
                                    "type": "array",
                                    "items": {
                                      "type": "array",
                                      "minItems": 4,
                                      "items": {
                                        "type": "array",
                                        "minItems": 2,
                                        "items": {
                                          "type": "string"
                                        }
                                      }
                                    }
                                  }
                                },
                                "bbox": {
                                  "type": "array",
                                  "minItems": 4,
                                  "items": {
                                    "type": "string"
                                  }
                                }
                              }
                            }
                          ]
                        }
                      },
                      "bbox": {
                        "type": "array",
                        "minItems": 4,
                        "items": {
                          "type": "string"
                        }
                      }
                    }
                  }
                ]
              },
              "bbox": {
                "type": "array",
                "minItems": 4,
                "items": {
                  "type": "string"
                }
              }
            }
          }
        },
        "bbox": {
          "type": "array",
          "minItems": 4,
          "items": {
            "type": "string"
          }
        }
      }
    }
  ]
}
)json"};

#endif