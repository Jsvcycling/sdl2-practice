/*
 * Copyright 2017 Joshua Vega
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

unsigned int load_shaders(const char *vertFilename, const char *fragFilename) {
  GLchar *vertSrc, *fragSrc;
  GLuint programId = glCreateProgram();
  int status_len = 0;
  long src_len = 0;
  FILE *file = NULL;

  file = fopen(vertFilename, "rb");

  if (file == NULL) {
    printf("Error opening vertex shader file.\n");
    return 0;
  }
  
  fseek(file, 0, SEEK_END);
  src_len = ftell(file);
  fseek(file, 0, SEEK_SET);
  vertSrc = (GLchar *)malloc(sizeof(GLchar) * src_len);
  fread(vertSrc, src_len, 1, file);
  vertSrc[src_len] = '\0';
  fclose(file);
  
  file = fopen(fragFilename, "rb");

  if (file == NULL) {
    printf("Error opening fragment shader file.\n");
    return 0;
  }
  
  fseek(file, 0, SEEK_END);
  src_len = ftell(file);
  fseek(file, 0, SEEK_SET);
  fragSrc = (GLchar *)malloc(sizeof(GLchar) * src_len);
  fread(fragSrc, src_len, 1, file);
  fragSrc[src_len] = '\0';
  fclose(file);

  if (programId == 0) {
    printf("Error creating OpenGL shader program.\n");
    return 0;
  }

  GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertId, 1, (const char **)&vertSrc, NULL);
  glCompileShader(vertId);
  glGetShaderiv(vertId, GL_INFO_LOG_LENGTH, &status_len);
  
  if (status_len > 0) {
    char buf[status_len];
    glGetShaderInfoLog(vertId, status_len, NULL, buf);
    printf("%s\n", vertSrc);
    printf("%s\n", buf);
    return 0;
  }
  
  glShaderSource(fragId, 1, (const char **)&fragSrc, NULL);
  glCompileShader(fragId);
  glGetShaderiv(fragId, GL_INFO_LOG_LENGTH, &status_len);

  if (status_len > 0) {
    char buf[status_len];
    glGetShaderInfoLog(fragId, status_len, NULL, buf);
    printf("%s\n", fragSrc);
    printf("%s\n", buf);
    return 0;
  }

  glAttachShader(programId, vertId);
  glAttachShader(programId, fragId);
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &status_len);

  if (status_len > 0) {
    char buf[status_len];
    glGetShaderInfoLog(fragId, status_len, NULL, buf);
    printf("%s\n", buf);
    return 0;
  }

  free(vertSrc);
  free(fragSrc);
    
  return programId;
}
