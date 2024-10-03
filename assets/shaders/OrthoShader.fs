#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 color;
uniform vec3 borderColor;
uniform float borderWidth;
uniform float borderRadius;
uniform vec2 resolution;

void main()
{
    // Convert TexCoords (0-1) to pixel space
    vec2 pos = TexCoords * resolution;

    // Correct the border radius to ensure it fits within the button dimensions
    float effectiveBorderRadius = min(borderRadius, min(resolution.x, resolution.y) / 2.0);
    
    // Define distances from the edges
    vec2 corner = vec2(effectiveBorderRadius, effectiveBorderRadius);
    vec2 minDist = min(pos, resolution - pos); // Distance to the closest edge

    // Handle rounded corners for outer border
    if (minDist.x < effectiveBorderRadius && minDist.y < effectiveBorderRadius) {
        // Calculate the distance to the corner arc (circle center at the corner of the button)
        vec2 cornerCenter = vec2(effectiveBorderRadius, effectiveBorderRadius);
        float dist = length(minDist - cornerCenter);

        // Discard pixels outside the corner arc for the outer border
        if (dist > effectiveBorderRadius) {
            discard;
        }
    }

    // Handle the inner color filling, ensuring it's inside the border and not overlapping
    float innerBorderLimit = borderWidth / 2.0;
    bool isInBorder = (
        TexCoords.x < (borderWidth / resolution.x) || TexCoords.x > (1.0 - borderWidth / resolution.x) ||
        TexCoords.y < (borderWidth / resolution.y) || TexCoords.y > (1.0 - borderWidth / resolution.y)
    );

    // Check if we are in the area of the rounded corner but inside the border
    float outerBorderLimit = borderWidth / resolution.x;

    // Now assign colors: border or button color, ensuring the button's fill respects the border width and radius
    if (isInBorder) {
        FragColor = vec4(borderColor, 1.0);  // Border color
    } else {
        // Make sure the inner color respects the rounded corners and stays within the border's area
        if (minDist.x >= innerBorderLimit && minDist.y >= innerBorderLimit) {
            FragColor = vec4(color, 1.0);  // Button inner color
        } else {
            discard;
        }
    }
}